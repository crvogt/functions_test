/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2015 Raytrix GmbH. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <conio.h>

// The Raytrix Light Field API
#include "Rx.Core\RxException.h"
#include "Rx.LFR\ApiLF.h"
#include "Rx.LFR\Cuda.h"
#include "Rx.LFR\CudaCompute.h"
#include "Rx.LFR\CudaDevice.h"
// Include CLUViz Tool DLL to display/load/save images.
#include "Rx.CluViz.Core.CluVizTool\CvCluVizTool.h"

bool m_bImageAvailable = false;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Process the image.
/// </summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProcessImage()
{
	// Preprocess image
	Rx::LFR::CApiLF::RxPreProcess();
	// Focus ray image to plane at depth dDepth
	Rx::LFR::CApiLF::RxRefocusBasic();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Callback, called when an image has been captured.
/// </summary>
///
/// <param name="uCamIdx">   The camera index that captured the image. </param>
/// <param name="pvContext"> The context pointer passed to Rx::ApiLF::RxCamRegisterImageCallback. </param>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageCallback(unsigned uCamIdx, void* pvContext)
{
	// Retrieve the image from the image and write the image data into the bound image.
	Rx::LFR::CApiLF::RxCamRetrieveImage();
	ProcessImage();

	m_bImageAvailable = true;
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
	unsigned uDeviceID, uMajor, uMinor;

	Rx::CRxString sxPath, sxFile;
	Rx::CRxString sxDevName, sxValue;

	// Initialize CLUVizTool
	printf("Initializing CLUVizTool...\n");
	CLUViz::Tool::Init();

	// Create an image view
	printf("Creating image view window...\n");
	int iView = 0;
	CLUViz::Tool::CreateViewImage(iView, 600, 100, 800, 600, "Image");

	try
	{
		// Initialize Raytrix Library with CUDA support using default library paths
		printf("Initializing API...\n");
		Rx::LFR::CApiLF::RxInit(true);

		////////////////////////////////////////////////////////////////////
		// List available CUDA devices and select one
		int iDevCnt = Rx::LFR::CApiLF::RxCudaDeviceCount();
		for (int iDev = 0; iDev < iDevCnt; ++iDev)
		{
			Rx::LFR::CApiLF::RxCudaDeviceProp(iDev, sxDevName, uMajor, uMinor);
			printf("CUDA Device %d: %s (%d.%d)\n", iDev, sxDevName.ToCString(), uMajor, uMinor);
		}

		// Automatic selection if no device ID or a negative device ID is given.
		Rx::LFR::CApiLF::RxCudaSelectDevice();

		// Get information on selected CUDA device
		//Rx::LFR::CApiLF:
		//Rx::LFR::CApiLF::RxGetPar(Rx::LFR::Params::EApiL)
		//Rx::LFR::CApiLF::RxGetPar(Rx::LFR::Params::ECudaDevice::ID::Name, sxDevName);
		//Rx::LFR::CApiLF::RxGetPar()
		//Rx::LFR::CApiLF::RxGetPar(Rx::LFR::Params::ECudaDevice::Name, sxDevName);

		/*
		Rx::LFR::CApiLF::RxGetPar(Rx::LFR::CApiLF::EPar::Cuda_DeviceName, sxDevName);
		Rx::LFR::CApiLF::RxGetPar(Rx::LFR::CApiLF::EPar::Cuda_DeviceID, uDeviceID);
		Rx::LFR::CApiLF::RxGetPar(Rx::ApiLF::EPar::Cuda_CapaMajor, uMajor);
		Rx::LFR::CApiLF::RxGetPar(Rx::ApiLF::EPar::Cuda_CapaMinor, uMinor);

		Rx::LFR::CApiLF::RxGetPar(Rx::LFR::Params::ECudaDevice::Name, sxDevName);
		*/


		//Rx::LFR::CApiLF::RxGetPar(Rx::LFR::Params::ECalib::ID::)

		//printf("Selected CUDA Device: %d, %s, (%d.%d)\n", uDeviceID, sxDevName.ToCString(), uMajor, uMinor);
		//printf("\n\n");

		////////////////////////////////////////////////////////////////////
		// Initialize cameras
		////////////////////////////////////////////////////////////////////

		printf("Initializing camera drivers...");
		unsigned uCamID = 1;
		Rx::LFR::CApiLF::RxCamOpen(uCamID);
		Rx::LFR::CApiLF::RxCamRegister();
		/*
		printf("done.\n");

		printf("Registering cameras...");
		Rx::ApiLF::RxCamRegister();
		printf("done.\n");

		// Register the image callback in the API
		Rx::ApiLF::RxCamRegisterImageCallback(Rx::ApiLF::TFuncCamImageCallback(ImageCallback), nullptr);

		////////////////////////////////////////////////////////////////////
		// Get information on available cameras
		////////////////////////////////////////////////////////////////////

		// Number of cameras available
		unsigned uCameraCount;
		Rx::ApiLF::RxGetPar(Rx::ApiLF::EPar::Cam_Count, uCameraCount);

		if (uCameraCount == 0)
		{
			printf("No cameras available. Press any key to end...\n");
			_getch();
			return -1;
		}
		printf("Number of cameras available: %d\n", uCameraCount);

		////////////////////////////////////////////////////////////////////
		// Get information on available camera calibration settings
		////////////////////////////////////////////////////////////////////

		// Work with camera 0
		unsigned uCamID = 0;

		// Before the calibration database for a camera can be accessed
		// the camera has to be opened.
		printf("Opening camera 0...");
		Rx::ApiLF::RxCamOpen(uCamID);
		printf("done.\n");

		printf("Binding camera 0 ...");
		Rx::ApiLF::RxCamBind(uCamID);
		printf("done.\n");

		printf("______________________________________________\n");
		printf("Camera %d:\n", uCamID);

		Rx::ApiLF::RxCamGetPar(uCamID, Rx::ApiLF::EPar::Cam_DriverName, sxValue);
		printf(">> Type: %s\n", sxValue.ToCString());

		Rx::ApiLF::RxCamGetPar(uCamID, Rx::ApiLF::EPar::Cam_HardwareId, sxValue);
		printf(">> ID  : %s\n", sxValue.ToCString());

		printf("\n\n");

		/////////////////////////////////////////////////////////////////
		// Capture images from camera
		Rx::ApiLF::RxSetPar(Rx::ApiLF::EPar::Proj_CurrentTargetView, unsigned(Rx::Projection::ESpace::ViewCamera));

		Rx::ApiLF::RxCamSetPar(Rx::ApiLF::EPar::Cam_TriggerMode, unsigned(Rx::Interop::Runtime30::Camera::ETriggerMode::Software_SnapShot));

		// Now start capturing images
		printf("Starting capture...");
		Rx::ApiLF::RxCamStartCapture();
		printf("done.\n\n");

		printf("\n\n");
		printf("Set camera parameter\n");
		printf("____________________\n");

		// Get the current camera exposure
		double dValue;
		Rx::ApiLF::RxCamGetPar(Rx::ApiLF::EPar::Cam_Exposure, dValue);

		//RxCamGetPar(uCamID, EPar::Cam_Exposure, dValue);
		printf("Init Exposure: %g\n", dValue);

		// Set the camera exposure in milliseconds
		Rx::ApiLF::RxCamSetPar(Rx::ApiLF::EPar::Cam_Exposure, 10.0);

		// Depending on the camera and other settings, the exposure
		// time set in the previous step may not be exactly available.
		// Read the exposure time again to see what the actual value is.
		Rx::ApiLF::RxCamGetPar(Rx::ApiLF::EPar::Cam_Exposure, dValue);
		printf("New Exposure: %g\n", dValue);

		bool bDoCapture   = true;
		bool bUpdateImage = false;
		double dFocus     = 0.5;

		// Loop until the user ends the program
		bool bEnd = false;
		while (!bEnd)
		{
			// Set API parameters
			Rx::ApiLF::RxSetPar(Rx::ApiLF::EPar::Focus_RelativeFocusPlane, dFocus);

			if (bDoCapture)
			{
				bDoCapture = false;

				// Trigger the camera
				Rx::ApiLF::RxCamTrigger();
			}

			if (bUpdateImage)
			{
				ProcessImage();
			}

			if (m_bImageAvailable)
			{
				// Get focused image from CUDA device
				Rx::CRxImage xImage;
				Rx::ApiLF::RxGetImage(Rx::ApiLF::EImgID::RefocusBasic, xImage);

				// Display the image
				CLUViz::Tool::ViewSetImage(iView, &xImage);

				printf("\nMenu:\n");
				printf("'c': Capture new image\n");
				printf("'+', '-': Change focus\n");
				printf("'q': End\n\n");

				switch (_getch())
				{
				case 'c':
					if (m_bImageAvailable)
					{
						bDoCapture        = true;
						m_bImageAvailable = false;
					}
					break;

				case '+':
					dFocus      += 0.05;
					bUpdateImage = true;
					break;

				case '-':
					dFocus      -= 0.05;
					bUpdateImage = true;
					break;

				case 'q':
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
		}

		printf("Stopping camera capture...");
		// Stop capturing
		Rx::ApiLF::RxCamStopCapture();
		printf("done.\n");

		// Close camera --> implies an unbind
		printf("Closing camera...");
		Rx::ApiLF::RxCamClose(uCamID);
		printf("done.\n");
	*/
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
	/*
	printf("Closing CLUViz Tool...");
	// Close all CLUViz Windows and free internally used memory
	CLUViz::Tool::Finalize();
	printf("done.\n");

	printf("Closing Raytrix API...");
	// Close Raytrix API, free all memory on host and CUDA device
	// and close all open cameras.
	Rx::ApiLF::RxFinalize();
	printf("done.\n");
	*/
	return 0;
}