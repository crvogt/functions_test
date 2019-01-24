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

		// Initialize CLUVizTool
		printf("Initializing CLUVizTool...\n");
		CLUViz::Tool::Init();

		// Create an image view
		printf("Creating image view window...\n");

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

		/************************************************************************/
		/* Work with one Camera (Id uID) and one GPU (Id uID)	                */
		/* Get information on available camera calibration settings	            */
		/************************************************************************/

		// Work with camera and GPU 0
		unsigned uID = 0;
		//unsigned testID = 1;

		// Get the camera from the camera server
		Rx::LFR::CCamera& xCamera = xCamServer.GetCamera(uID);
		//Rx::LFR::CCamera& xCameraTest = xCamServer.GetCamera(testID);

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

		// Create the visualization
		int iHandle;
		CLUViz::Tool::CreateViewImage(iHandle, 0, 0, 1000, 800, sxCameraName.ToCString());

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

		//Exposure settings
		float exposureVal = 1.0;
		bool bExposureUp = true;

		// Loop until the user ends the program
		bool bEnd = false;
		while (!bEnd)
		{
			printf("Start of loop\n");
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

			// Pre-process raw light field image before calling any processing functions
			xCudaCompute.Compute_PreProcess();

			// Get refocus image from CUDA device
			printf("Download image from CUDA device...\n");
			Rx::CRxImage xOutputImage;
			pxImages->Download(Rx::LFR::EImage::Processed_Normalized, &xOutputImage);

			// Display the image
			CLUViz::Tool::ViewSetImage(iHandle, &xOutputImage);

			// Set the camera exposure in milliseconds
			if (bExposureUp) {
				exposureVal += 2.0;
				if (exposureVal > 50.0) {
					bExposureUp = false;
				}
			}
			else {
				exposureVal -= 2.0;
				if (exposureVal < 2.0) {
					bExposureUp = true;
				}
			}
			xCamera.SetProperty(Rx::Interop::Runtime30::Camera::EProperty::Exposure, exposureVal);

			bDoCapture = true;
			bUpdateImage = false;
		}

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
