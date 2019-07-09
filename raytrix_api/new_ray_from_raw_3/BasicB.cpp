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
#include "Rx.LFR\Parameters.h"
#include "Rx.LFR\Enums.Values.h"

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
	bool calc_depth = false;
	bool calc_proc = false;
	bool calc_dm = true;
	int num_files = 20;

	std::cout << "Calculating depth?: " << calc_depth << std::endl;
	try {
		std::cout << "starting...\n";

		// Construct path to ray image
		Rx::CRxString sxRayFile = "C:\\Users\\carson\\gray_to_png\\0034045116\\plant.ray";
		Rx::CRxString sxGrayPngFile = "C:\\Users\\carson\\gray_to_png\\0034045116\\gray.png";
		
		for(int it = 0; it < num_files; it++){
			Rx::CRxString sxRawPngFile = "E:\\raytrix_images\\low_light_raw\\";
			sxRawPngFile += it;
			sxRawPngFile += ".png";
			Rx::CRxString writeOut = "E:\\raytrix_images\\low_light_dm_raw\\";
			writeOut += it;
			writeOut += ".png";

			// Ray image
			Rx::CRxImage xRayImage;

			// Initialize Raytrix Library with CUDA support using default library paths
			printf("Initializing API...\n");
			Rx::LFR::CApiLF::RxInit(true);

			// Automatic CUDA device selection if no device ID or a negative device ID is given.
			printf("Selecting CUDA device...\n");
			Rx::LFR::CApiLF::RxCudaSelectDevice();

			// Load a ray image
			printf("Loading image '%s'...\n", sxRayFile.ToCString());
			unsigned uImgID = Rx::LFR::CApiLF::RxRayLoad(sxRayFile);

			//// Bind the loaded ray image. This copies the ray image to the CUDA device.
			Rx::LFR::CApiLF::RxRayBind(uImgID);

			//// Get normalized image from CUDA device
			Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Raw, xRayImage);

			Rx::FileIO::CImage xImageFile;

			Rx::CRxImage xRawImage;
			Rx::CRxImage xImgLum, xImgBayer;
			Rx::CRxImage imageLumGray;
			Rx::CRxImage xGrayImage;

			// Load raw image
			printf("Loading raw image '%s'...\n", sxRawPngFile.ToCString());
			xImageFile.Read(&xImgLum, sxRawPngFile);
			xImgBayer.Create(xImgLum.GetFormat().m_iWidth, xImgLum.GetFormat().m_iHeight, Rx::Interop::Runtime28::EPixelType::BayerGB, Rx::Interop::Runtime28::EDataType::UByte, xImgLum.GetDataPtr());
			
			// Load gray image
			printf("Loading raw image '%s'...\n", sxGrayPngFile.ToCString());
			xImageFile.Read(&xGrayImage, sxGrayPngFile);
			/*
			CLUViz::Tool::ViewSetImage(iView, &xGrayImage);

			// Wait for user to press any key.
			printf("Press any key...\n");
			_getch();
			*/
			// Now apply the raw image and the gray image to the loaded ray image.
			Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Raw, xImgBayer);
			xImgBayer.Destroy();


			Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Gray, xGrayImage);
			xGrayImage.Destroy();

			Rx::LFR::CApiLF::RxRaySave(sxRayFile, true);
			// Get normalized image from CUDA device
			if (calc_proc) {
				printf("Preprocessing...\n");
				Rx::LFR::CApiLF::RxPreProcess();
				std::cout << "Getting preprocessed lf\n";
				Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Processed_Normalized, xRayImage);
			}
			else if (calc_dm) {
				printf("Preprocessing...\n");
				Rx::LFR::CApiLF::RxPreProcess();

				// Set Pre-Process Parameters
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::PreProc_DenoiseNLM_Enable, 0U);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::PreProc_DenoiseNLM_FilterDia, 4U);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::PreProc_DenoiseNLM_NoiseLevel, 0.15);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::PreProc_DenoiseNLM_BlendFactor, 0.2);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::PreProc_Sharp1_Enable, 1U);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::PreProc_Sharp1_BlurStdDev, 2.5);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::PreProc_Sharp1_Factor, 1.8);

				// Set Depth Parameters
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_NearResolutionLevel, 3U);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_MinStdDeviation, 0.00);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_MinCorrelation, 0.9);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_PatchDiameter, 4U);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_PatchStride, 1U);

				// Depth Fill Parameters
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_Fill_Enabled, 0U);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_Fill_IterCnt, 4U);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_Fill_IterSize, 1U);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_Fill_Complete, 0U);

				// Depth Fill Bilateral filter
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_Enabled, 1U);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_FilterRadius, 5U);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_Edge, 0.1);
				Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_Range, 5.0);

				Rx::LFR::CApiLF::RxDepthRay();
				Rx::LFR::CApiLF::RxDepthMap(Rx::LF::ESpace::View_Object_Pinhole);
				Rx::LFR::CApiLF::RxDepth3D();
				Rx::LFR::CApiLF::RxDepthColorCode(Rx::LF::ESpace::View_Object_Pinhole);
				Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::DepthMapColored_View_Object_Pinhole, xRayImage);
			}
			else {
				printf("Preprocessing...\n");
				Rx::LFR::CApiLF::RxPreProcess();
				std::cout << "Getting total focus image\n";
				Rx::LFR::CApiLF::RxDepthRay();
				Rx::LFR::CApiLF::RxDepthMap(Rx::LF::ESpace::ID::View_Virtual);
				Rx::LFR::CApiLF::RxTotalFocus(Rx::LF::ESpace::ID::View_Virtual);
				Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::TotalFocus_View_Virtual, xRayImage);
			}

			Rx::FileIO::CImage writeImg;
			writeImg.Write(&xRayImage, writeOut);
		}
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