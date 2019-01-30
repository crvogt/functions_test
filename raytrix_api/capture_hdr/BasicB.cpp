/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Attempting to capture an hdr image set
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <conio.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "Rx.LFR/LightFieldRuntime.h"
#include "Rx.LFR/ICudaData.h"
#include "Rx.LFR/CameraServer.h"
#include "Rx.LFR/CalibrationManager.h"
#include "Rx.LFR/Cuda.h"
#include "Rx.LFR/CudaCompute.h"
#include "Rx.LFR/ImageQueue.h"

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

		// Write into buffer
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

static void ImageCaptured(const Rx::CRxImage& xImage, unsigned uCamIdx, void* pvContext)
{
	OnImageCaptured(xImage, uCamIdx);
}

int main(int argc, char* argv[])
{
	try
	{
		// Authenticate MGPU runtime
		printf("Authenticate LFR...\n");
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
			printf("No camera found\n");
			return 0;
		}

		printf("Number of cameras available: %d\n", xCamServer.GetCameraCount());

		// Quit the application if there is no Cuda device
		if (Rx::LFR::CCuda::GetDeviceCount() == 0)
		{
			printf("No Cuda device found\n");
			return 0;
		}

		// Work with camera and GPU 0
		unsigned uID = 0;
		
		// Get the camera from the camera server
		Rx::LFR::CCamera& xCamera = xCamServer.GetCamera(uID);

		// Open the camera
		xCamera.Open();

		// Add a image captured callback. This method gets called for every captured camera image and more details are given there
		xCamera.AddImageCapturedCallback(ImageCaptured, nullptr);

		// Set up the image buffer properties
		unsigned uBufferSize = 3;
		bool bOverwrite = true;//false;

		// Create buffer within the given size and with the given overwrite flag
		m_xCamBuffer.Initialize(uBufferSize, bOverwrite);

		// Load the default calibration of the camera (and load the gray image too)
		Rx::LFR::CCalibration xDefaultCalibration;
		Rx::LFR::CCalibrationManager::LoadDefaultCalibration(xDefaultCalibration, xCamera, true);

		// For this example just work with one camera and one GPU
		xCudaCompute.SetCudaDevice(Rx::LFR::CCuda::GetDevice(uID));
		xCudaCompute.ApplyCalibration(xDefaultCalibration, true);
		xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned) Rx::Interop::Runtime28::EDataType::UByte);

		// Get the camera name
		Rx::CRxString sxCameraName = Rx::LFR::CCalibrationManager::GetCameraName(xCamera);

		// Now start capturing images
		xCamera.Start(Rx::Interop::Runtime30::Camera::ETriggerMode::Software_SnapShot);

		// Set the camera exposure in milliseconds
		xCamera.SetProperty(Rx::Interop::Runtime30::Camera::EProperty::Exposure, 5.0f);

		bool bDoCapture   = true;
		bool bUpdateImage = false;
		
		// Get the image access interface.
		Rx::LFR::ICudaDataImages* pxImages = static_cast<Rx::LFR::ICudaDataImages*>(xCudaCompute.GetInterface(Rx::LFR::Interfaces::ECudaCompute::Images));

		// Get the first image in the Queue
		Rx::CRxImage xCapturedImage;


		/**************fibonacci exp bracketing*************/
		// Set number of exposures in time T
		float T = 1000.0; //ms
		float exposure = 3.0;
		float exposure_sum = 0.0;
		float temp_exp1 = 0.0;
		float temp_exp2 = 0.0;
		std::vector<float> exposure_vec;
		int counter = 0;

		while(exposure_sum <= T){
			if(counter == 0){
				exposure_vec.push_back(exposure);
				exposure_sum += exposure;
				temp_exp1 = exposure;
				temp_exp2 = exposure;
				counter++;
			}
			else{
				exposure = temp_exp1 + temp_exp2;
				if((exposure_sum + exposure) < T){
					exposure = temp_exp1 + temp_exp2;
					exposure_sum += exposure;
					exposure_vec.push_back(exposure);
					temp_exp1 = temp_exp2;
					temp_exp2 = exposure;
					counter++;
				}
				else{
					break;
				}
			}
		}


		// Loop until the user ends the program
		bool bEnd = false;
		
		counter = 0;
		for(int iter = 0; iter < exposure_vec.size(); iter++){
			//printf("Start of loop\n");
			if (bDoCapture)
			{
				bDoCapture = false;

				// Trigger the camera
				xCamera.Trigger();
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
			printf("Download image from CUDA device...\n");
			Rx::CRxImage xOutputImage;
			pxImages->Download(Rx::LFR::EImage::Raw, &xOutputImage);

			// Set the camera exposure in milliseconds	
			std::cout << "\nSetting exposure!\n";		
			xCamera.SetProperty(Rx::Interop::Runtime30::Camera::EProperty::Exposure, exposure_vec[iter]);

			// Check how quickly this is set
			std::cout << "Going into infinite while loop" << std::enld;
			while(true){}
			// Then save the lf

			bDoCapture = true;
			bUpdateImage = false;
			counter++;
		}
		milliseconds diff = duration_cast<milliseconds>(end - start);
		std::cout << "total time: " << diff.count() << "ms" << std::endl;
		std::cout << "exposure time: " << expTimeTotal << "ms" << std::endl;
		// Stop capturing
		xCamera.Stop();

		// Close camera --> implies an unbind
		xCamera.Close();

		// Finalize Cuda and the runtime
		Rx::LFR::CLightFieldRuntime::End();

		// Wait for user to press any key.
		printf("Press any key...\n");
		_getch();
	}
	catch (Rx::CRxException& ex)
	{
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
