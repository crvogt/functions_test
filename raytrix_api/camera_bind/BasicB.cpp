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

		// Iterate over all available Cuda devices
		printf("Listing Cuda devices...\n");
		for (int iIdx = 0; iIdx < Rx::LFR::CCuda::GetDeviceCount(); iIdx++)
		{
			const Rx::LFR::CCudaDevice& xCuda = Rx::LFR::CCuda::GetDevice(iIdx);

			Rx::CRxString sxName;
			xCuda.GetParams().GetValue(Rx::LFR::Params::ECudaDevice::Name, sxName);

			double dClockMHz;
			xCuda.GetParams().GetValue(Rx::LFR::Params::ECudaDevice::ClockFrequencyMHz, dClockMHz);

			double dGlobalMemMB;
			xCuda.GetParams().GetValue(Rx::LFR::Params::ECudaDevice::TotalGlobalMemoryMB, dGlobalMemMB);

			printf("%d: %s, Clock: %.0f MHz, Memory: %.0f MB\n", iIdx, sxName.ToCString(), dClockMHz, dGlobalMemMB);
		}

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

		printf("Number of Cuda devices available: %d\n", Rx::LFR::CCuda::GetDeviceCount());

		/************************************************************************/
		/* Work with one Camera (Id uID) and one GPU (Id uID)	                */
		/* Get information on available camera calibration settings	            */
		/************************************************************************/

		// Work with camera and GPU 0
		unsigned uID = 0;

		// Get the camera from the camera server
		Rx::LFR::CCamera& xCamera = xCamServer.GetCamera(uID);

		// Open the camera
		printf("Opening camera 0...");
		xCamera.Open();
		printf("done.\n");

		// Add a image captured callback. This method gets called for every captured camera image and more details are given there
		xCamera.AddImageCapturedCallback(ImageCaptured, nullptr);

		printf("______________________________________________\n");
		printf("Camera %d:\n", uID);

		printf(">> Type: %s\n", xCamera.GetDriverName().ToCString());

		printf(">> ID  : %s\n", xCamera.GetInternalSerial().ToCString());

		printf("\n\n");

		// Set up the image buffer properties
		unsigned uBufferSize = 3;
		bool bOverwrite      = false;

		printf("______________________________________________\n");
		printf("Camera Image Buffer %d:\n", uID);

		printf(">> Buffersize: %u\n", uBufferSize);

		printf(">> Overwrite  : %s\n", bOverwrite ? "Yes" : "No");

		printf("\n\n");

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
		printf("Starting capture...");
		xCamera.Start(Rx::Interop::Runtime30::Camera::ETriggerMode::Software_SnapShot);
		printf("done.\n\n");

		printf("\n\n");
		printf("Set camera parameter\n");
		printf("____________________\n");

		// Get the current camera exposure
		float fValue;
		xCamera.GetProperty(Rx::Interop::Runtime30::Camera::EProperty::Exposure, fValue);
		printf("Init Exposure: %g\n", fValue);

		// Set the camera exposure in milliseconds
		xCamera.SetProperty(Rx::Interop::Runtime30::Camera::EProperty::Exposure, 10.0f);

		// Get the new camera exposure
		xCamera.GetProperty(Rx::Interop::Runtime30::Camera::EProperty::Exposure, fValue);
		printf("New Exposure: %g\n", fValue);

		bool bDoCapture   = true;
		bool bUpdateImage = false;
		double dFocus     = 0.5;

		// Get the image access interface.
		Rx::LFR::ICudaDataImages* pxImages = static_cast<Rx::LFR::ICudaDataImages*>(xCudaCompute.GetInterface(Rx::LFR::Interfaces::ECudaCompute::Images));

		// Get the first image in the Queue
		Rx::CRxImage xCapturedImage;

		// Loop until the user ends the program
		bool bEnd = false;
		while (!bEnd)
		{
			if (bDoCapture)
			{
				bDoCapture = false;

				// Trigger the camera
				xCamera.Trigger();
			}

			// Wait for the image buffer to be not empty
			if (!m_xCamBuffer.WaitForNotEmpty(1000))
			{
				continue;
			}

			// Check if a new image should be get from the image buffer or the previous image sould be updated
			if (!bUpdateImage)
			{
				if (!m_xCamBuffer.MoveOut(xCapturedImage))
				{
					// Wait again! This functions says that it waits until a frame is available
					continue;
				}
			}

			// Upload the image as the new raw image of all further CUDA computations
			printf("Uploading image to Cuda compute instance...\n");
			xCudaCompute.UploadRawImage(xCapturedImage);

			// Pre-process raw light field image before calling any processing functions
			printf("Pre-processing light field image...\n");
			xCudaCompute.Compute_PreProcess();

			// Compute refocus image
			printf("Computing refocus image on depth %g...\n", dFocus);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Focus_RelativeFocusPlane, dFocus);
			xCudaCompute.Compute_RefocusBasic();

			// Get refocus image from CUDA device
			printf("Download image from CUDA device...\n");
			Rx::CRxImage xOutputImage;
			pxImages->Download(Rx::LFR::EImage::RefocusBasic, &xOutputImage);

			// Display the image
			CLUViz::Tool::ViewSetImage(iHandle, &xOutputImage);

			printf("\nMenu:\n");
			printf("'c': Capture new image\n");
			printf("'+', '-': Change focus\n");
			printf("'q': End\n\n");

			switch (_getch())
			{
			case 'c':
				bDoCapture   = true;
				bUpdateImage = false;
				break;

			case '+':
				printf("said +\n");
				printf("before: %f\n", dFocus);
				dFocus      += 0.05;
				printf("after: %f\n", dFocus);
				bUpdateImage = true;
				break;

			case '-':
				printf("said -\n");
				dFocus      -= 0.05;
				bUpdateImage = true;
				break;

			case 'q':
				printf("quitting\n");
				bEnd = true;
				break;
			}

			if (dFocus < 0.0)
			{
				dFocus = 0.0;
			}
			else if (dFocus >= 1.0)
			{
				dFocus = 0.95;
			}
		}

		printf("Stopping camera capture...");
		// Stop capturing
		xCamera.Stop();
		printf("done.\n");

		// Close camera --> implies an unbind
		printf("Closing camera...");
		xCamera.Close();
		printf("done.\n");

		// Finalize Cuda and the runtime
		Rx::LFR::CLightFieldRuntime::End();

		// The example is finished
		printf("finished.\n");

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
