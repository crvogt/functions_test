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
		float exposure_val, collect_time;
		std::string file_location, file_location_zero, file_location_one;

		if (argc <= 1) {
			std::cout << "file_location, processed_bool, visualize, delay_catch, exposure_val, save_feed, collect_time\n";
			return 0;
		}
		else {
			file_location = std::string(argv[1]);
			processed_bool = std::stoi(std::string(argv[2]));
			visualize = std::stoi(std::string(argv[3]));
			delay_catch = std::stoi(std::string(argv[4]));
			exposure_val = std::stof(std::string(argv[5]));
			save_feed = std::stoi(std::string(argv[6]));
			collect_time = std::stof(std::string(argv[7]));
		}

		std::cout << "fl: " << file_location << " pb: " << processed_bool << " vis: " << visualize << " dc: " << delay_catch << " ev: " << exposure_val << std::endl;

		// Prepare saving vars
		Rx::LFR::CSeqFileWriter seq_out;
		Rx::FileIO::CImage write_lf;
		Rx::CRxString write_file;
		int write_count = 0;

		// Authenticate MGPU runtime
		std::cout << "Authenticate LFR...\n";
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
		unsigned gpuID = 0;
		unsigned camID = 0;

		// Get the camera from the camera server
		std::cout << "Camera from server\n";
		Rx::LFR::CCamera& cam = xCamServer.GetCamera(camID);

		// Open the camera
		cam.Open();
		
		// Add a image captured callback. This method gets called for every captured camera image and more details are given there
		std::cout << "Adding callback\n";
		cam.AddImageCapturedCallback(ImageCaptured, nullptr);

		// Set up the image buffer properties
		unsigned uBufferSize = 3;
		bool bOverwrite = true;//false;

		// Create buffer within the given size and with the given overwrite flag
		std::cout << "Initializing buffer\n";
		m_xCamBuffer.Initialize(uBufferSize, bOverwrite);

		// Load the default calibration of the camera (and load the gray image too)
		Rx::LFR::CCalibration calib;
		Rx::LFR::CCalibrationManager::LoadDefaultCalibration(calib, cam, true);

		// For this example just work with one camera and one GPU
		xCudaCompute.SetCudaDevice(Rx::LFR::CCuda::GetDevice(gpuID));
		xCudaCompute.ApplyCalibration(calib, true);
		xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned) Rx::Interop::Runtime28::EDataType::UByte);

		// Get the camera name
		Rx::CRxString cam_name = Rx::LFR::CCalibrationManager::GetCameraName(cam);

		// Create the visualization
		//Initialize CLUVizTool
		int iHandle, tHandle;
		if (visualize) {
			std::cout << "Initializing CLUVizTool...\n";
			CLUViz::Tool::Init();

			// Create an image view
			std::cout << "Creating image view window...\n";

			CLUViz::Tool::CreateViewImage(iHandle, 0, 0, 1000, 800, cam_name.ToCString());
		}

		// Now start capturing images
		std::cout << "Starting cameras...\n";
		cam.Start(Rx::Interop::Runtime30::Camera::ETriggerMode::Camera_FreeRun);

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
		cam.SetProperty(Rx::Interop::Runtime30::Camera::EProperty::Exposure, exposure_val);
		
		std::cout << "Initializing timer....\n";
		time_point<Clock> start = Clock::now();
		time_point<Clock> end;

		std::cout << "In main loop...\n";
		time_t timer1, timer2, timer3;
		double start_seconds = 0.0;
		//Get current time
		time(&timer1);

		// sequence prep
		Rx::CRxImage xOutputImage;
		Rx::LFR::CRayImage ray;
		Rx::CRxString ray_file = "C://Users//cvogt//Desktop//gray_to_png//0034035116//plant.ray";
		Rx::LFR::CRayFileReader::Read(ray_file, ray);
		unsigned int bufCount = 2U;
		unsigned int doubleShotMode = 2U;
		
		int counter = 5;
		int cam_sum = 0;
		bool run_flag = true;
		bool collect_flag;

		while (run_flag) {
			// Collect?
			std::cout << "Collect?\n";
			std::cin >> collect_flag;

			if (collect_flag) {
				//Create the correct directory (iterate to new dir)
				std::string temp_file_location = file_location + std::to_string(counter) + "//";
				std::cout << "File location: " << temp_file_location.c_str() << std::endl;

				write_file = temp_file_location.c_str();
				write_file += "0.rays";

				// Can only bind one sequence at a time
				seq_out.Open(write_file, bufCount);
				seq_out.StartWriting(ray.GetFormat(), ray.GetCalibration(), ray.GetMetaData(), doubleShotMode);

				time(&timer1);
				std::cout << "Recording...\n";
				double seconds = 0.0;
				while (seconds < collect_time)
				{
					// Wait for the image buffer to be not empty
					if (!m_xCamBuffer.WaitForNotEmpty(1))
					{
						m_xCamBuffer.Clear();
					}

					if (!m_xCamBuffer.MoveOut(xCapturedImage))
					{
						// Wait again! This functions says that it waits until a frame is available
						continue;
					}

					if (save_feed) {
						cam_sum++;
						
						seq_out.WriteFrame(xCapturedImage);
					}

					// Display the image
					if (visualize) {
						CLUViz::Tool::ViewSetImage(iHandle, &xCapturedImage);
					}

					bDoCapture = true;
					bUpdateImage = false;
					time(&timer2);
					seconds = difftime(timer2, timer1);
				}
				seq_out.Close();
				counter++;
				std::cout << "Next dir: " << counter << std::endl;

			}
			else {
				run_flag = false;
			}
		}
	
		std::cout << "\ncam num: " << cam_sum;

		std::cout << "Stopping camera(s)...\n";
		cam.Stop();

		// Close camera --> implies an unbind
		std::cout << "Closing camera(s)...\n";
		cam.Close();

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
