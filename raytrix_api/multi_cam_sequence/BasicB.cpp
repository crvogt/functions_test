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
#include <time.h>
#include <Windows.h>

#include "Rx.LFR/LightFieldRuntime.h"
#include "Rx.LFR/ICudaData.h"
#include "Rx.LFR/CameraServer.h"
#include "Rx.LFR/CalibrationManager.h"
#include "Rx.LFR/Cuda.h"
#include "Rx.LFR/CudaCompute.h"
#include "Rx.LFR/ImageQueue.h"
#include "Rx.FileIO/Rx.FileIO.Image.h"
#include "Rx.LFR/RayFileReader.h"
#include "Rx.LFR/SeqFileWriter.h"
#include "Rx.LFR/ApiLF.h"

#include "Rx.Core/RxException.h"
#include "Rx.CluViz.Core.CluVizTool/CvCluVizTool.h"

/// <summary> The camera buffer loop. </summary>
Rx::LFR::CImageQueue m_xCamBuffer;

//Set some clock namespaces
using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::microseconds;
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

std::chrono::high_resolution_clock::time_point start_hr = std::chrono::high_resolution_clock::now();

void OnImageCaptured(const Rx::CRxImage& xImage, unsigned uCamIdx)
{
	try
	{
		// Make a copy of the provided image. We don't know if this image is reused by the camera SDK or by another handler
		std::chrono::high_resolution_clock::time_point cur_tp = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> span = std::chrono::duration_cast<std::chrono::duration<double>>(cur_tp - start_hr);
		Rx::CRxImage xCapturedImage;
		xCapturedImage.Create(&xImage);
		//std::cout << "\nspan: " << span.count();
		xCapturedImage.SetTimestampID(span.count(), uCamIdx);
		//xCapturedImage.SetID(uCamIdx);

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

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
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
		float exposure_val_zero, exposure_val_one, collect_time;
		std::string file_location, file_location_zero, file_location_one;

		if (argc <= 1) {
			std::cout << "file_location, processed_bool, visualize, delay_catch, exposure_val_zero, exposure_val_one, save_feed, collect_time\n";
			return 0;
		}
		else {
			file_location = std::string(argv[1]);
			processed_bool = std::stoi(std::string(argv[2]));
			visualize = std::stoi(std::string(argv[3]));
			delay_catch = std::stoi(std::string(argv[4]));
			exposure_val_zero = std::stof(std::string(argv[5]));
			exposure_val_one = std::stof(std::string(argv[6]));
			save_feed = std::stoi(std::string(argv[7]));
			collect_time = std::stof(std::string(argv[8]));
		}

		/*bool dir_success = CreateDirectory((LPCWSTR)file_location.c_str(), NULL);
		if (dir_success) {
			std::cout << "Created base dir: " << file_location << std::endl;
		}
		else {
			if (dirExists(file_location)) {
				std::cout << "dir already exists\n";
			}
			else {
				std::cout << "could not create " << file_location << std::endl;
			}
		}*/

		file_location_zero = file_location + "\\0";
		file_location_one = file_location + "\\1";

		std::cout << "file_location_zero: " << file_location_zero << std::endl;
		std::cout << "file_location_one: " << file_location_one << std::endl;

		/*bool dir_success_zero = CreateDirectory((LPCWSTR)file_location_zero.c_str(), NULL);
		bool dir_success_one = CreateDirectory((LPCWSTR)file_location_one.c_str(), NULL);
		if (dir_success_zero && dir_success_one) {
			std::cout << "successfully created: " << file_location_zero << " and: " << file_location_one << std::endl;
		}
		else {
			std::cout << "did not create: " << file_location_zero << std::endl;
			bool dir_exists = dirExists(file_location_zero);
			if (dir_exists) {
				std::cout << "directory already exists\n";
			}
			else {
				std::cout << "directory doesn't exist\n";
			}
			return 0;
		}*/

		// Prepare saving vars
		Rx::LFR::CSeqFileWriter seq_out_zero;
		Rx::LFR::CSeqFileWriter seq_out_one;
		Rx::FileIO::CImage write_lf;
		Rx::CRxString write_file_zero;
		Rx::CRxString write_file_one;
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
		Rx::LFR::CCalibration calib_one;
		Rx::LFR::CCalibrationManager::LoadDefaultCalibration(calib_zero, cam_zero, true);
		Rx::LFR::CCalibrationManager::LoadDefaultCalibration(calib_one, cam_one, true);

		// For this example just work with one camera and one GPU
		xCudaCompute.SetCudaDevice(Rx::LFR::CCuda::GetDevice(gpuID_zero));
		xCudaCompute.ApplyCalibration(calib_zero, true);
		xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned) Rx::Interop::Runtime28::EDataType::UByte);
		xCudaCompute.ApplyCalibration(calib_one, true);

		// Get the camera name
		Rx::CRxString cam_name_zero = Rx::LFR::CCalibrationManager::GetCameraName(cam_zero);
		Rx::CRxString cam_name_one = Rx::LFR::CCalibrationManager::GetCameraName(cam_one);

		// Create the visualization
		//Initialize CLUVizTool
		int iHandle, tHandle;
		if (visualize) {
			std::cout << "Initializing CLUVizTool...\n";
			CLUViz::Tool::Init();

			// Create an image view
			std::cout << "Creating image view window...\n";

			CLUViz::Tool::CreateViewImage(iHandle, 0, 0, 1000, 800, cam_name_zero.ToCString());
			CLUViz::Tool::CreateViewImage(tHandle, 0, 0, 1000, 800, cam_name_one.ToCString());
		}

		// Now start capturing images
		std::cout << "Starting cameras...\n";
		cam_zero.Start(Rx::Interop::Runtime30::Camera::ETriggerMode::Camera_FreeRun);
		cam_one.Start(Rx::Interop::Runtime30::Camera::ETriggerMode::Camera_FreeRun);

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

		std::cout << "Initializing timer....\n";
		time_point<Clock> start = Clock::now();
		time_point<Clock> end;

		std::cout << "In main loop...\n";
		time_t timer1, timer2, timer3;
		double seconds = 0.0;
		double start_seconds = 0.0;
		//Get current time
		time(&timer1);

		// sequence prep
		Rx::CRxImage xOutputImage;
		Rx::LFR::CRayImage ray_zero;
		Rx::LFR::CRayImage ray_one;
		Rx::CRxString ray_file_zero = "C://Users//cvogt//Desktop//gray_to_png//0034045116//plant.ray";
		Rx::CRxString ray_file_one = "C://Users//cvogt//Desktop//gray_to_png//0034035116//plant.ray";
		Rx::LFR::CRayFileReader::Read(ray_file_zero, ray_zero);
		Rx::LFR::CRayFileReader::Read(ray_file_one, ray_one);
		unsigned int bufCount = 2U;
		unsigned int doubleShotMode = 2U;
		write_file_zero = file_location_zero.c_str();
		write_file_zero += "0.rays";
		write_file_one = file_location_one.c_str();
		write_file_one += "0.rays";
		seq_out_zero.Open(write_file_zero, bufCount);
		seq_out_zero.StartWriting(ray_zero.GetFormat(), ray_zero.GetCalibration(), ray_zero.GetMetaData(), doubleShotMode);
		/*seq_out_one.Open(write_file_one, bufCount);
		seq_out_one.StartWriting(ray_one.GetFormat(), ray_one.GetCalibration(), ray_one.GetMetaData(), doubleShotMode);
*/
		int counter = 0;
		int cam_0_sum = 0;
		int cam_1_sum = 1;
		std::cout << "RECORDING in 3 seconds\n";
		while (start_seconds < 3.0) {
			time(&timer3);
			start_seconds = difftime(timer3, timer1);
			std::cout << start_seconds << std::endl;
		}
		//auto start_time = std::chrono::steady_clock::now();
		//std::chrono::high_resolution_clock::time_point start_hr = std::chrono::high_resolution_clock::now();
		time(&timer1);
		std::cout << "Recording...\n";
		while (seconds < collect_time)
		{
			
			// Wait for the image buffer to be not empty
			if (!m_xCamBuffer.WaitForNotEmpty(1))
			{
				m_xCamBuffer.Clear();
			}

			//// Check if a new image should be get from the image buffer or the previous image sould be updated
			//if (!bUpdateImage)
			//{
			if (!m_xCamBuffer.MoveOut(xCapturedImage))
			{
				// Wait again! This functions says that it waits until a frame is available
				//printf("Waiting for frame to be available\n");
				continue;
			}
			//}
		
			// Upload the image as the new raw image of all further CUDA computations
			//xCapturedImage.
			//xCudaCompute.UploadRawImage(xCapturedImage);
			//xCudaCompute.UploadRawImage()

			// Get image from CUDA device
			//printf("Download image from CUDA device...\n");
			/*if (!processed_bool) {
				pxImages->Download(Rx::LFR::EImage::Raw, &xOutputImage);
				
			}
			else {
				xCudaCompute.Compute_PreProcess();
				pxImages->Download(Rx::LFR::EImage::Processed_Normalized, &xOutputImage);
			}*/
			
			if (save_feed) {
				
				//std::cout << "ID: " << xCapturedImage.GetID() << std::endl;
				if (xCapturedImage.GetID() == 0) {
					cam_0_sum++;
				}
				else if(xCapturedImage.GetID() == 1) {
					cam_1_sum++;
				}

				//std::chrono::system_clock::now()
				/*std::chrono::high_resolution_clock::time_point cur_tp = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> span = std::chrono::duration_cast<std::chrono::duration<double>>(cur_tp - start_hr);*/
				// std::cout << "span: " << span.count() << std::endl;
					
				//xCapturedImage.SetTimestamp(span.count());
				seq_out_zero.WriteFrame(xCapturedImage);
				//std::cout << counter + 1 << std::endl;
				counter++;
					
				/*write_file = file_location_zero.c_str();
				write_file += write_count_zero;
				write_file += ".png";
				write_count_zero++;*/
				//bMainCam = false;

				// Write lf to file
				//write_lf.Write(&xOutputImage, write_file);
				
			}

			// Display the image
			if (visualize) {
				CLUViz::Tool::ViewSetImage(iHandle, &xOutputImage);
				CLUViz::Tool::ViewSetImage(tHandle, &xOutputImage);
			}

			bDoCapture = true;
			bUpdateImage = false;
			time(&timer2);
			seconds = difftime(timer2, timer1);
			//std::cout << seconds << std::endl;
			/*if (seconds >= 10.0) {
				std::cout << "Breaking...\n";
				break;
			}*/
		}
	
		std::cout << "\ncam zero num: " << cam_0_sum;
		std::cout << "\ncam one num: " << cam_1_sum << std::endl;

		std::cout << "Stopping camera(s)...\n";
		cam_zero.Stop();
		cam_one.Stop();

		// Close camera --> implies an unbind
		std::cout << "Closing camera(s)...\n";
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
