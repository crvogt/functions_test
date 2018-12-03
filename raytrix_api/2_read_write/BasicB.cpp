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
		// Construct path to ray image
		Rx::CRxString sxRayFile = "C:\\Users\\carson\\Desktop\\raytrix_api_tests\\rx_img.ray";
		//Get png files
		Rx::CRxString grayPng = "C:\\Users\\carson\\Desktop\\gray_to_png\\5_Gray.png";
		Rx::CRxString lowShut = "C:\\Users\\carson\\Desktop\\gray_to_png\\5.png";
		Rx::CRxImage xRawPNGImage;
		Rx::FileIO::CImage xImageFile;
		xImageFile.Read(&xRawPNGImage, lowShut);

		// Initialize CLUVizTool
		printf("Initializing CLUVizTool...\n");
		CLUViz::Tool::Init();
		printf("Creating image view window...\n");
		int iView = 0;
		CLUViz::Tool::CreateViewImage(iView, 0, 0, 1000, 800, "");

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

		// Bind the loaded ray image. This copies the ray image to the CUDA device.
		printf("Binding image...\n");
		Rx::LFR::CApiLF::RxRayBind(uImgID);

		// Get normalized image from CUDA device
		Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Raw, xRayImage);
		//Rx::LFR::CApiLF::RxGetImage()
		// Display the image
		CLUViz::Tool::ViewSetImage(iView, &xRayImage);

		// Wait for user to press any key.
		printf("Press any key...\n");
		_getch();
		
		// Start importing the .png files
		//Rx::FileIO::CImage xImageFile;
		Rx::CRxString sxRawPngFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\5.png";
		Rx::CRxImage xRawImage;
		Rx::CRxString sxGrayPngFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\5_Gray.png";
		Rx::CRxImage xGrayImage;

		// Load raw image
		printf("Loading raw image '%s'...\n", sxRawPngFile.ToCString());
		xImageFile.Read(&xRawImage, sxRawPngFile);
		CLUViz::Tool::ViewSetImage(iView, &xRawImage);

		// Wait for user to press any key.
		printf("Press any key...\n");
		_getch();

		// Load gray image
		printf("Loading raw image '%s'...\n", sxGrayPngFile.ToCString());
		xImageFile.Read(&xGrayImage, sxGrayPngFile);
		CLUViz::Tool::ViewSetImage(iView, &xGrayImage);


		// Wait for user to press any key.
		printf("Press any key...\n");
		_getch();

		// Now apply the raw image and the gray image to the loaded ray image.
		Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Raw, xRawImage);
		xRawImage.Destroy();


		Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Gray, xGrayImage);
		xGrayImage.Destroy();

		// Deactivate white image to draw grid into raw image
		//Rx::LFR::CApiLF::RxSetPar()
		//Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECalib::ID::IsMasterCalibrated, sxGrayPngFile);
		//Rx::ApiLF::RxSetPar(Rx::ApiLF::EPar::Ray_ApplyWhiteImage, 1U);
		//How about this????
		//Rx::LFR::CApiLF::RxCalibDBReloadBoundCalib(1);
		
		// Process image with no white image
		printf("Preprocessing normalized...\n");
		Rx::LFR::CApiLF::RxPreProcess();

		sxRayFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\Demo_04_NEW.ray";
		//Rx::LFR::CApiLF::RxRaySave()
		Rx::LFR::CApiLF::RxRaySave(sxRayFile, true);

		// Get normalized image from CUDA device
		Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Processed_Normalized, xRayImage);

		// Display the image
		CLUViz::Tool::ViewSetImage(iView, &xRayImage);

		// Wait for user to press any key.
		printf("Press any key...\n");
		_getch();

	return 0;
}