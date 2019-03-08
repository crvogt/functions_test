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
	bool calc_depth = true;
	std::cout << "Calculating depth?: " << calc_depth << std::endl;
	try {
		std::cout << "starting...\n";
		for (int iter = 0; iter < 10; iter++) {
			// Construct path to ray image
			//Rx::CRxString sxRayFile = "C:\\Users\\carson\\Desktop\\raytrix_api_tests\\rx_img.ray";
			Rx::CRxString sxRayFile = "C:\\Users\\cvogt\\Desktop\\gray_to_png\\0034045116\\plant.ray";

			/*
			// Initialize CLUVizTool
			printf("Initializing CLUVizTool...\n");
			CLUViz::Tool::Init();
			printf("Creating image view window...\n");
			int iView = 0;
			CLUViz::Tool::CreateViewImage(iView, 0, 0, 1000, 800, "");
			*/
			// Ray image
			Rx::CRxImage xRayImage;

			///////////////////////////////////////////////////////////////
			/// Initialize and prepare
			///////////////////////////////////////////////////////////////

			// Initialize Raytrix Library with CUDA support using default library paths
			printf("Initializing API...\n");
			Rx::LFR::CApiLF::RxInit(true);

			// Automatic CUDA device selection if no device ID or a negative device ID is given.
			printf("Selecting CUDA device...\n");
			Rx::LFR::CApiLF::RxCudaSelectDevice();

			///////////////////////////////////////////////////////////////
			/// Basic image processing
			///////////////////////////////////////////////////////////////

			// Load a ray image
			printf("Loading image '%s'...\n", sxRayFile.ToCString());
			unsigned uImgID = Rx::LFR::CApiLF::RxRayLoad(sxRayFile);

			//// Bind the loaded ray image. This copies the ray image to the CUDA device.
			//printf("Binding image...\n");
			Rx::LFR::CApiLF::RxRayBind(uImgID);

			//// Get normalized image from CUDA device
			Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Raw, xRayImage);
			////Rx::LFR::CApiLF::RxGetImage()
			//// Display the image
			/*
			CLUViz::Tool::ViewSetImage(iView, &xRayImage);

			//// Wait for user to press any key.
			printf("Press any key...\n");
			_getch();
			*/
			// Start importing the .png files
			Rx::FileIO::CImage xImageFile;
			Rx::CRxString sxRawPngFile = "E:\\hdr\\fibonacci\\0\\raw\\";
			sxRawPngFile += iter;
			sxRawPngFile += ".png";
			Rx::CRxImage xRawImage;
			Rx::CRxImage xImgLum, xImgBayer;
			Rx::CRxImage imageLumGray;
			Rx::CRxString sxGrayPngFile = "C:\\Users\\cvogt\\Desktop\\gray_to_png\\0034045116\\gray.png";
			Rx::CRxImage xGrayImage;

			// Load raw image
			printf("Loading raw image '%s'...\n", sxRawPngFile.ToCString());
			xImageFile.Read(&xImgLum, sxRawPngFile);
			xImgBayer.Create(xImgLum.GetFormat().m_iWidth, xImgLum.GetFormat().m_iHeight, Rx::Interop::Runtime28::EPixelType::BayerGB, Rx::Interop::Runtime28::EDataType::UByte, xImgLum.GetDataPtr());
			/*
			CLUViz::Tool::ViewSetImage(iView, &xImgBayer);
			// Wait for user to press any key.
			printf("Press any key...\n");
			_getch();
			*/
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

			// Process image with no white image
			printf("Preprocessing...\n");
			Rx::LFR::CApiLF::RxPreProcess();

			Rx::LFR::CApiLF::RxRaySave(sxRayFile, true);
			// Get normalized image from CUDA device
			if (!calc_depth) {
				std::cout << "Getting preprocessed lf\n";
				Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Processed_Normalized, xRayImage);
			}
			else {
				std::cout << "Getting total focus image\n";
				Rx::LFR::CApiLF::RxDepthRay();
				Rx::LFR::CApiLF::RxDepthMap(Rx::LF::ESpace::ID::View_Virtual);
				Rx::LFR::CApiLF::RxTotalFocus(Rx::LF::ESpace::ID::View_Virtual);
				Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::TotalFocus_View_Virtual, xRayImage);
			}

			Rx::FileIO::CImage writeImg;
			Rx::CRxString writeOut = "E:\\hdr\\fibonacci\\0\\tf\\";
			writeOut += iter;
			writeOut += ".png";
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