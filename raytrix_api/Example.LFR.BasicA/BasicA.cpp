/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Raytrix GmbH. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  This example demonstrates:                                          */
/*      - Working with an image.                                        */
/*      - Calculating refocus image                                     */
/************************************************************************/

#include <conio.h>
#include <iostream>
#include "Rx.LFR\LightFieldRuntime.h"
#include "Rx.LFR\RayFileReader.h"
#include "Rx.LFR\Cuda.h"
#include "Rx.LFR\CudaCompute.h"
#include "Rx.Core\RxException.h"

int main(int argc, char* argv[])
{
	try
	{
		/*if (argc != 2)
		{
			printf("Please provide the full file name of a ray image as the first command line argument. yo\n");
			printf("Press any key to end program...\n");
			_getch();
			return 0;
		}
		*/
		// Construct path to ray image
		//std::string fileName = "C:\Users\carson\Desktop\raytrix_api_tests\Demo_02.ray";
		Rx::CRxString sxFile = "C:\\Users\\carson\\Desktop\\raytrix_api_tests\\Demo_02.ray";

		/************************************************************************/
		/* Initialize and Prepare                                               */
		/************************************************************************/

		// Authenticate MGPU runtime C:\Users\carson\Desktop\raytrix_api_tests\test_rays.rays                                                              
		("Authenticate LFR...\n");
		Rx::LFR::CLightFieldRuntime::Authenticate();

		// Enumerate all CUDA devices at the beginning
		Rx::LFR::CCuda::EnumerateCudaDevices();

		// Load ray image
		printf("Loading image '%s'...\n", sxFile.ToCString());
		Rx::LFR::CRayImage xInputImage;
		Rx::LFR::CRayFileReader::Read(sxFile, xInputImage);

		// Assign the CUDA device and the calibration
		printf("Selecting CUDA device...\n");
		Rx::LFR::CCudaCompute xCudaCompute;
		xCudaCompute.SetCudaDevice(Rx::LFR::CCuda::GetDevice(Rx::LFR::CCuda::GetDeviceCount() - 1));
		xCudaCompute.ApplyCalibration(xInputImage.GetCalibration(), true);
		xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned) Rx::Interop::Runtime28::EDataType::UByte);

		// Upload the image as the new raw image of all further CUDA computations
		printf("Uploading image to Cuda compute instance...\n");
		xCudaCompute.UploadRawImage(xInputImage);

		/************************************************************************/
		/* Image Processing                                                     */
		/************************************************************************/

		// Pre-process raw light field image before calling any processing functions
		printf("Pre-processing light field image...\n");
		xCudaCompute.Compute_PreProcess();

		// Focus ray image to plane at depth 0.5
		printf("Focusing on plane...\n");
		xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Focus_RelativeFocusPlane, 0.5);
		xCudaCompute.Compute_RefocusBasic();

		// Get the image access interface. This interface allows:
		Rx::LFR::ICudaDataImages* pxImages = static_cast<Rx::LFR::ICudaDataImages*>(xCudaCompute.GetInterface(Rx::LFR::Interfaces::ECudaCompute::Images));

		// Get focused image from CUDA device
		printf("Download image from CUDA device...\n");
		Rx::CRxImage xOutputImage;
		pxImages->Download(Rx::LFR::EImage::RefocusBasic, &xOutputImage);

		// Now work with the image.
		// ...

		printf("finished.\n");

		printf("Press any key...\n");
		_getch();

		// Finalizes the light field runtime and ends Cuda --> Finalizes all resources
		Rx::LFR::CLightFieldRuntime::End();
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
