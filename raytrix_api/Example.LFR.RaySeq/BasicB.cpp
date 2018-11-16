/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Raytrix GmbH. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  This example demonstrates:                                          */
/*      - Working with an image.                                        */
/*      - Processing image                                              */
/*      - Setting parameter                                             */
/*      - Displaying results                                            */
/************************************************************************/

#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Rx.Core\RxException.h"
#include "Rx.CluViz.Core.CluVizTool\CvCluVizTool.h"
#include "Rx.FileIO\Rx.FileIO.Image.h"

#include "Rx.LFR\LightFieldRuntime.h"
#include "Rx.LFR\Cuda.h"
#include "Rx.LFR\CudaCompute.h"
#include "Rx.LFR\RayFileReader.h"
#include "Rx.LFR\ApiLF.h"
#include "Rx.LFR\Enums.Values.h"
#include "Rx.LFR\SeqFileReader.h"

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
int main(int argc, char* argv[]){
		// Setup cuda stuff...
		// Initialize CLUVizTool
		printf("Initializing CluVizTool...\n");
		CLUViz::Tool::Init();

		// Create an image view...
		//printf("Creating image view window...\n");
		//int iHandle;
		//CLUViz::Tool::CreateViewImage(iHandle, 0, 0, 1000, 800, "");

		// Autheniticate MGPU runtime
		printf("Authenticate LFR...\n");
		Rx::LFR::CLightFieldRuntime::Authenticate();

		// Enumerate allCUDA devices at the beginning
		Rx::LFR::CCuda::EnumerateCudaDevices();
	
		//Rx::CRxString sxFile = "C:\\Users\\carson\\Desktop\\raytrix_api_tests\\test_rays.rays";
		Rx::CRxString sxFile = "C:\\Users\\carson\\Pictures\\Raytrix\\Export\\test_set_3\\ray_test_3.rays.rays";

		unsigned int uFrameBufferCount = 2;
		
		std::cout << "File location: " << sxFile.ToCString() << std::endl;
		
		//Rx::LFR::CApiLF::RxRaySeqOpen(sxFile, Rx::LFR::ERaySeqMode::ID::Read, uFrameBufferCount);
		Rx::LFR::CSeqFileReader readObj;
		
		
		readObj.Open(sxFile, uFrameBufferCount);

		std::cout << "file size: " << readObj.GetFileSize();
		std::cout << "\nframe count: " << readObj.GetFrameCount() << std::endl;
		//readObj.ReadFrame();
		//readObj.GetFrameIndex();
		
		Rx::LFR::CRayImage xInputImage;
		Rx::LFR::CCudaCompute xCudaCompute;
		
		// Create an image view
		printf("Creating image view window...\n");
		int iHandle;
		CLUViz::Tool::CreateViewImage(iHandle, 0, 0, 1000, 800, "");

		readObj.StartReading(xInputImage);

		for (int iter = 0; iter < readObj.GetFrameCount(); iter=iter+10) {

			Rx::FileIO::CImage saveImg;
			saveImg.
			// Assign the CUDA device and the calibration
			printf("Selecting CUDA device...\n");
			//Rx::LFR::CCudaCompute xCudaCompute;
			xCudaCompute.SetCudaDevice(Rx::LFR::CCuda::GetDevice(Rx::LFR::CCuda::GetDeviceCount() - 1));
			xCudaCompute.ApplyCalibration(xInputImage.GetCalibration(), true);
			//Rx::LFR::CCalibration inputCalib = xInputImage.GetCalibration();
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned)Rx::Interop::Runtime28::EDataType::UByte);

			// Upload the image as the new raw image of all further CUDA computations
			printf("Uploading image to cuda compute instance...\n");
			xCudaCompute.UploadRawImage(xInputImage);

			// Get the image access interface. This interface allows:
			Rx::LFR::ICudaDataImages* pxImages = static_cast<Rx::LFR::ICudaDataImages*>(xCudaCompute.GetInterface(Rx::LFR::Interfaces::ECudaCompute::Images));

			printf("Starting image processing...\n");
			printf("\n");

			//Show raw light field image
			printf("Displaying raw light field image...\n");
			CLUViz::Tool::ViewSetImage(iHandle, &xInputImage);
			printf("Press any key...\n");
			printf("\n");
			_getch();

			// Pre-process raw light field image before calling any processing functions
			printf("Pre-processing light field image...\n");
			xCudaCompute.Compute_PreProcess();

			// Get processed normalized image from CUDA device
			printf("Download image from CUDA device...\n");
			Rx::CRxImage xOutputImage;
			pxImages->Download(Rx::LFR::EImage::Processed_Normalized, &xOutputImage);

			//Show processed light field image
			printf("Displaying raw light field image...\n");
			CLUViz::Tool::ViewSetImage(iHandle, &xOutputImage);
			printf("Press any key...\n");
			printf("\n");
			_getch();

			//Set depth parameters
			printf("Set depth parameters...");

			// Set Pre-Process Parameters
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DenoiseNLM_Enable, 1U);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DenoiseNLM_FilterDia, 4U);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DenoiseNLM_NoiseLevel, 0.15);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DenoiseNLM_BlendFactor, 0.2);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_Sharp1_Enable, 1U);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_Sharp1_BlurStdDev, 2.5);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_Sharp1_Factor, 1.8);

			// Set Depth Parameters
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_NearResolutionLevel, 3U);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_MinStdDeviation, 0.00);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_MinCorrelation, 0.9);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_PatchDiameter, 4U);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_PatchStride, 1U);

			// Depth Fill Parameters
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Enabled, 1U);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_IterCnt, 4U);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_IterSize, 1U);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Complete, 1U);

			// Depth Fill Bilateral filter
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_Enabled, 1U);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_FilterRadius, 5U);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_Edge, 0.1);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_Range, 5.0);

			// Calculate the raw depth and subsequently the fused depth map in the view camera space additionally process the depth 3D image
			printf("Computing depth...");
			xCudaCompute.Compute_DepthRay();
			xCudaCompute.Compute_DepthMap(Rx::LF::ESpace::View_Object_Pinhole);
			xCudaCompute.Compute_Depth3D();

			// Color code the calculated depth to visualize it properly
			xCudaCompute.Compute_DepthColorCode(Rx::LF::ESpace::View_Object_Pinhole);

			// Get depth color code image from CUDA device
			printf("Download image from CUDA device...\n");
			pxImages->Download(Rx::LFR::EImage::DepthMapColored_View_Object_Pinhole, &xOutputImage);

			// Display the image
			printf("Displaying depth image...\n");
			CLUViz::Tool::ViewSetImage(iHandle, &xOutputImage);
			// Wait for user to press any key.
			printf("Press any key...\n");
			printf("\n");
			_getch();

			//Let's us iterate through frames
			readObj.SetFrameIndex(iter + 1);
			readObj.ReadFrame(xInputImage);
		}
		/*
		// Pre-process raw light field image before calling any processing functions
		printf("Pre-processing light field image...\n");
		xCudaCompute.Compute_PreProcess();

		// Get processed normalized image from CUDA device
		printf("Download image from CUDA device...\n");
		Rx::CRxImage xOutputImage;
		pxImages->Download(Rx::LFR::EImage::Processed_Normalized, &xOutputImage);

		// Display the image
		CLUViz::Tool::ViewSetImage(iHandle, &xOutputImage);

		// Wait for user to press any key.
		printf("Press any key...\n");
		printf("\n");
		_getch();
		*/
		return 0;
}
