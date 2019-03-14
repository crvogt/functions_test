/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Raytrix GmbH. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  This example demonstrates:                                          */
/*      - Working with a camera.                                        */
/*      - Calculating refocus image                                     */
/*      - Displaying result                                             */
/************************************************************************/

#include <conio.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <string>

#include "Rx.LFR/LightFieldRuntime.h"
#include "Rx.LFR/ICudaData.h"
#include "Rx.LFR/CameraServer.h"
#include "Rx.LFR/CalibrationManager.h"
#include "Rx.LFR/Cuda.h"
#include "Rx.LFR/CudaCompute.h"
#include "Rx.LFR/ImageQueue.h"
#include "Rx.FileIO\Rx.FileIO.Image.h"

#include "Rx.Core\RxException.h"
#include "Rx.CluViz.Core.CluVizTool/CvCluVizTool.h"

/// <summary> The camera buffer loop. </summary>
Rx::LFR::CImageQueue m_xCamBuffer;

//Set some clock namespaces
using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;
using std::this_thread::sleep_for;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Executes the image captured action.
/// </summary>
///
/// <param name="xImage">  The image. </param>
/// <param name="uCamIdx"> The camera index. </param>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OnImageCaptured(const Rx::CRxImage& xImage, unsigned uCamIdx)
{
	try
	{
		// Make a copy of the provided image. We don't know if this image is reused by the camera SDK or by another handler
		Rx::CRxImage xCapturedImage;
		xCapturedImage.Create(&xImage);

		/************************************************************************/
		/* Write into buffer                                                    */
		/************************************************************************/
		if (!m_xCamBuffer.MoveIn(std::move(xCapturedImage)))
		{
			// Buffer is full and overwrite is disabled
			// This is a lost frame
			return;
		}
	}
	catch (Rx::CRxException& ex)
	{
		printf("Exception occured:\n%s\n\n", ex.ToString(true).ToCString());
		printf("Press any key to end program...\n");
		_getch();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void ImageCaptured(const Rx::CRxImage& xImage, unsigned uCamIdx, void* pvContext)
{
	OnImageCaptured(xImage, uCamIdx);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Main entry-point for this application.
/// </summary>
///
/// <param name="argc"> Number of command-line arguments. </param>
/// <param name="argv"> Array of command-line argument strings. </param>
///
/// <returns> Exit-code for the process - 0 for success, else an error code. </returns>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	try
	{
		/************************************************************************/
		/* Initialize and Prepare                                               */
		/************************************************************************/

		bool processed_bool, visualize, save_feed;
		int delay_catch;
		float exposure_val_zero, exposure_val_one;
		std::string file_location_zero, file_location_one;

		if (argc <= 1) {
			std::cout << "file_location_zero, file_location_one, processed_bool, visualize, delay_catch, exposure_val_zero, exposure_val_one, save_feed\n";
			return 0;
		}
		else {
			file_location_zero = std::string(argv[1]);
			file_location_one = std::string(argv[2]);
			processed_bool = std::stoi(std::string(argv[3]));
			visualize = std::stoi(std::string(argv[4]));
			delay_catch = std::stoi(std::string(argv[5]));
			exposure_val_zero = std::stoi(std::string(argv[6]));
			exposure_val_one = std::stoi(std::string(argv[7]));
			save_feed = std::stoi(std::string(argv[8]));
		}

		// Prepare saving vars
		Rx::FileIO::CImage write_lf;
		Rx::CRxString write_file;
		int write_count_zero = 0;
		int write_count_one = 0;

		// Authenticate MGPU runtime
		std::cout << "Autheticate LFR...\n";
		Rx::LFR::CLightFieldRuntime::Authenticate();

		/// <summary> The camera server class that is able to find attached cameras. </summary>
		Rx::LFR::CCameraServer xCamServer;
		/// <summary> This is the Cuda compute instance. </summary>
		Rx::LFR::CCudaCompute xCudaCompute;

		// Enumerate all CUDA devices at the beginning
		Rx::LFR::CCuda::EnumerateCudaDevices();

		// Start to find cameras. This is an synchronous call and we wait here until the find process has been finished
		xCamServer.FindCameras();

		// Quit the application if there is no camera
		if (xCamServer.GetCameraCount() == 0)
		{
			std::cout << "No camera found\n";
			return 0;
		}

		std::cout << "Number of cameras available: " << xCamServer.GetCameraCount() << std::endl;

		// Quit the application if there is no Cuda device
		if (Rx::LFR::CCuda::GetDeviceCount() == 0)
		{
			printf("No Cuda device found\n");
			return 0;
		}
		
		/************************************************************************/
		/* Work with one Camera (Id uID) and one GPU (Id uID)	                */
		/* Get information on available camera calibration settings	            */
		/************************************************************************/

		// Work with camera and GPU 0
		unsigned gpuID_zero = 0;
		unsigned camID_zero = 0;
		unsigned camID_one = 1;

		// Get the camera from the camera server
		std::cout << "Camera from server\n";
		Rx::LFR::CCamera& cam_zero = xCamServer.GetCamera(camID_zero);
		Rx::LFR::CCamera& cam_one = xCamServer.GetCamera(camID_one);

		// Open the camera
		cam_zero.Open();
		cam_one.Open();
		
		// Add a image captured callback. This method gets called for every captured camera image and more details are given there
		std::cout << "Adding callback\n";
		cam_zero.AddImageCapturedCallback(ImageCaptured, nullptr);
		cam_one.AddImageCapturedCallback(ImageCaptured, nullptr);

		// Set up the image buffer properties
		unsigned uBufferSize = 3;
		bool bOverwrite = true;//false;

		// Create buffer within the given size and with the given overwrite flag
		std::cout << "Initializing buffer\n";
		m_xCamBuffer.Initialize(uBufferSize, bOverwrite);

		// Load the default calibration of the camera (and load the gray image too)
		Rx::LFR::CCalibration calib_zero;
		Rx::LFR::CCalibrationManager::LoadDefaultCalibration(calib_zero, cam_zero, true);

		Rx::LFR::CCalibration calib_one;
		Rx::LFR::CCalibrationManager::LoadDefaultCalibration(calib_one, cam_one, true);

		// For this example just work with one camera and one GPU
		xCudaCompute.SetCudaDevice(Rx::LFR::CCuda::GetDevice(gpuID_zero));
		xCudaCompute.ApplyCalibration(calib_zero, true);
		xCudaCompute.ApplyCalibration(calib_one, true);
		xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned) Rx::Interop::Runtime28::EDataType::UByte);

		// Get the camera name
		Rx::CRxString cam_name_zero = Rx::LFR::CCalibrationManager::GetCameraName(cam_zero);
		Rx::CRxString cam_name_one = Rx::LFR::CCalibrationManager::GetCameraName(cam_one);

		// Create the visualization
		//Initialize CLUVizTool
		int iHandle, iTestHandle;
		if (visualize) {
			std::cout << "Initializing CLUVizTool...\n";
			CLUViz::Tool::Init();

			// Create an image view
			std::cout << "Creating image view window...\n";

			CLUViz::Tool::CreateViewImage(iHandle, 0, 0, 1000, 800, cam_name_zero.ToCString());
			CLUViz::Tool::CreateViewImage(iTestHandle, 0, 0, 1000, 800, cam_name_one.ToCString());
		}

		// Now start capturing images
		std::cout << "Starting cameras...\n";
		cam_zero.Start(Rx::Interop::Runtime30::Camera::ETriggerMode::Software_SnapShot);
		cam_one.Start(Rx::Interop::Runtime30::Camera::ETriggerMode::Software_SnapShot);

		bool bDoCapture   = true;
		bool bUpdateImage = false;
		
		// Get the image access interface.
		Rx::LFR::ICudaDataImages* pxImages = static_cast<Rx::LFR::ICudaDataImages*>(xCudaCompute.GetInterface(Rx::LFR::Interfaces::ECudaCompute::Images));

		// Get the first image in the Queue
		Rx::CRxImage xCapturedImage;

		// Loop until the user ends the program
		bool bEnd = false;
		bool bMainCam = true;
		
		std::cout << "Setting exposure...\n";
		//Set exposure values
		cam_zero.SetProperty(Rx::Interop::Runtime30::Camera::EProperty::Exposure, exposure_val_zero);
		cam_one.SetProperty(Rx::Interop::Runtime30::Camera::EProperty::Exposure, exposure_val_one);
		
		std::cout << "In main loop...\n";
		while (!bEnd)
		{
			if (bDoCapture)
			{
				bDoCapture = false;

				// Trigger the camera
				if (bMainCam) {
					cam_zero.Trigger();
					//bMainCam = false;
				}
				else{
					cam_one.Trigger();
					//bMainCam = true;
				}
			}

			// Wait for the image buffer to be not empty
			if (!m_xCamBuffer.WaitForNotEmpty(-1))
			{
				m_xCamBuffer.Clear();
			}

			// Check if a new image should be get from the image buffer or the previous image sould be updated
			if (!bUpdateImage)
			{
				if (!m_xCamBuffer.MoveOut(xCapturedImage))
				{
					// Wait again! This functions says that it waits until a frame is available
					printf("Waiting for frame to be available\n");
					continue;
				}
			}

			// Upload the image as the new raw image of all further CUDA computations
			xCudaCompute.UploadRawImage(xCapturedImage);

			// Get refocus image from CUDA device
			//printf("Download image from CUDA device...\n");
			Rx::CRxImage xOutputImage;
			if (!processed_bool) {
				pxImages->Download(Rx::LFR::EImage::Raw, &xOutputImage);
			}
			else {
				xCudaCompute.Compute_PreProcess();
				pxImages->Download(Rx::LFR::EImage::Processed_Normalized, &xOutputImage);
			}

			if (save_feed) {
				if (bMainCam) {
					write_file = file_location_zero.c_str();
					write_file += write_count_zero;
					write_file += ".png";
					write_count_zero++;
					bMainCam = false;
				}
				else {
					write_file = file_location_one.c_str();
					write_file += write_count_one;
					write_file += ".png";
					write_count_one++;
					bMainCam = true;
				}
				// Write lf to file
				write_lf.Write(&xOutputImage, write_file);
				if (bMainCam) {
					sleep_for(milliseconds(delay_catch));
				}
			}
			else {
				if (bMainCam)
					bMainCam = false;
				else
					bMainCam = true;
			}

			// Display the image
			if (visualize) {
				if (bMainCam) {
					CLUViz::Tool::ViewSetImage(iHandle, &xOutputImage);
				}
				else {
					CLUViz::Tool::ViewSetImage(iTestHandle, &xOutputImage);
				}
			}

			bDoCapture = true;
			bUpdateImage = false;
		}

		cam_zero.Stop();
		cam_one.Stop();

		// Close camera --> implies an unbind
		cam_zero.Close();
		cam_one.Close();

		// Finalize Cuda and the runtime
		Rx::LFR::CLightFieldRuntime::End();

		// Wait for user to press any key.
		printf("Press any key...\n");
		_getch();
	}
	catch(Rx::CRxException& ex){
		printf("Exception occured:\n%s\n\n", ex.ToString(true).ToCString());
		printf("Press any key to end program...\n");
		_getch();
		return -1;
	}
	catch (Rx::IException31& ex)
	{
		printf("Exception occured:\n%s\n\n", ex.GetMessageText());
		printf("Press any key to end program...\n");
		_getch();
		return -1;
	}

	return 0;
}
