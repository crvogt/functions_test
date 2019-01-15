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
	try{
	// Construct path to ray image
	//Rx::CRxString sxRayFile = "C:\\Users\\carson\\Desktop\\raytrix_api_tests\\rx_img.ray";
		Rx::CRxString sxRayFile = "C:\\Users\\cvogt\\Desktop\\gray_to_png\\plant.ray";

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

	//// Bind the loaded ray image. This copies the ray image to the CUDA device.
	//printf("Binding image...\n");
	Rx::LFR::CApiLF::RxRayBind(uImgID);

	//// Get normalized image from CUDA device
	Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Raw, xRayImage);
	////Rx::LFR::CApiLF::RxGetImage()
	//// Display the image
	CLUViz::Tool::ViewSetImage(iView, &xRayImage);

	//// Wait for user to press any key.
	printf("Press any key...\n");
	_getch();

	// Start importing the .png files
	Rx::FileIO::CImage xImageFile;
	Rx::CRxString sxRawPngFile = "C:\\Users\\cvogt\\Desktop\\gray_to_png\\color_test.png";
	Rx::CRxImage xRawImage;
	Rx::CRxImage xImgLum, xImgBayer;
	Rx::CRxImage imageLumGray;
	Rx::CRxString sxGrayPngFile = "C:\\Users\\cvogt\\Desktop\\gray_to_png\\b_gray.png";
	Rx::CRxImage xGrayImage;

	// Load raw image
	printf("Loading raw image '%s'...\n", sxRawPngFile.ToCString());
	xImageFile.Read(&xImgLum, sxRawPngFile);
	//Rx::CRxImage imgBayer;
	xImgBayer.Create(xImgLum.GetFormat().m_iWidth, xImgLum.GetFormat().m_iHeight, Rx::Interop::Runtime28::EPixelType::BayerGB, Rx::Interop::Runtime28::EDataType::UByte, xImgLum.GetDataPtr());
	//imgBayer.Create(imageLum.GetFormat().m_iWidth, imageLum.GetFormat().m_iHeight, Rx::Interop::Runtime28::EDataType::UByte, imageLum.GetDataPtr());
	
	//imageLum.ConvertType(xRawImage, Rx::Interop::Runtime28::EPixelType::BayerRG,
	//	Rx::Interop::Runtime28::EDataType::UByte);
	//while (true) {}
	CLUViz::Tool::ViewSetImage(iView, &xImgBayer);
	// Wait for user to press any key.
	printf("Press any key...\n");
	_getch();

	//imageLum.ConvertType(xRawImage, Rx::Interop::Runtime28::EPixelType::BayerGR,
	//	Rx::Interop::Runtime28::EDataType::UByte);

	// Load gray image
	printf("Loading raw image '%s'...\n", sxGrayPngFile.ToCString());
	xImageFile.Read(&xGrayImage, sxGrayPngFile);
	CLUViz::Tool::ViewSetImage(iView, &xGrayImage);

	// Wait for user to press any key.
	printf("Press any key...\n");
	_getch();
	
	// Now apply the raw image and the gray image to the loaded ray image.
	Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Raw, xImgBayer);
	xImgBayer.Destroy();


	Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Gray, xGrayImage);
	xGrayImage.Destroy();

	//Rx::LFR::CApiLF::
	// Deactivate white image to draw grid into raw image
	//Rx::LFR::CApiLF::RxSetPar()
	//Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECalib::ID::IsMasterCalibrated, sxGrayPngFile);
	//Rx::ApiLF::RxSetPar(Rx::ApiLF::EPar::Ray_ApplyWhiteImage, 1U);
	//How about this????
	//Rx::LFR::CApiLF::RxCalibDBReloadBoundCalib(1);
	//Rx::LFR::CApiLF::

	// Process image with no white image
	printf("Preprocessing normalized...\n");
	//unsigned int drrr = 1;
	//Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::PreProc_Demosaic_Enable, drrr);
	Rx::LFR::CApiLF::RxPreProcess();
	
	//Rx::LFR::CApiLF::RxDepthRay();

	//Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::PreProc_Demosaic_B);
	//Rx::LFR::CApiLF::RxSetPar()
	//Rx::LFR::CApiLF::RxSetPar(Rx::Interop::Runtime30::)
	//Rx::LFR::CApiLF::RxTotalFocus(Rx::LF::ESpace::ID::Object);
	//Rx::LFR::CApiLF::
	//Rx::LFR::CApiLF::RxTotalFocus(Rx::LF::ESpace::ID::View_Virtual);
	//Rx::LFR::CApiLF::RxRaySave()
	Rx::LFR::CApiLF::RxRaySave(sxRayFile, true);

	// Get normalized image from CUDA device
	Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Processed_Normalized, xRayImage);
	//Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::TotalFocus_View_Virtual, xRayImage);

	Rx::FileIO::CImage writeImg;
	Rx::CRxString writeOut = "C:\\Users\\cvogt\\Desktop\\gray_to_png\\check.png";
	writeImg.Write(&xRayImage, writeOut);
	//sxRayFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\Demo_04_NEW.ray";

	// Display the image
	CLUViz::Tool::ViewSetImage(iView, &xRayImage);

	// Wait for user to press any key.
	printf("Press any key...\n");
	_getch();

	//Rx::LFR::CApiLF::RxRefocusBasic()
	//Rx::LFR::Params::ECudaCompute::ID::Focus_RelativeFocusPlane(0.4);    //Focus_RelativeFocusPlane = 0.4;
	//Rx::LFR::Params::ECudaCompute::Focus_RelativeFocusPlane
	/*
	double refocVal = 0.0;
	while (refocVal < 1.0) {
		Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::ID::Focus_RelativeFocusPlane, refocVal);
		Rx::LFR::CApiLF::RxRefocusBasic();
		Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::RefocusBasic, xRayImage);
		//// Display the image
		CLUViz::Tool::ViewSetImage(iView, &xRayImage);

		//// Wait for user to press any key.
		printf("Press any key...\n");
		_getch();
		refocVal += 0.1;
		std::cout << "refocVal: " << refocVal << std::endl;
	}
	*/
	Rx::LFR::CApiLF::RxDepthRay();
	Rx::LFR::CApiLF::RxDepthMap(Rx::LF::ESpace::ID::View_Virtual);
	Rx::LFR::CApiLF::RxTotalFocus(Rx::LF::ESpace::ID::View_Virtual);
	Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::TotalFocus_View_Virtual, xRayImage);
	CLUViz::Tool::ViewSetImage(iView, &xRayImage);
	
	Rx::CRxString outFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\origLowTF.png";
	writeImg.Write(&xRayImage, outFile);

	//// Wait for user to press any key.
	printf("Press any key...\n");
	_getch();
	//Rx::LFR::CApiLF::RxSetPar();
	/*Rx::LFR::Params::EParticleTracking::;
	Rx::LFR::Params::ECudaCompute::Focus_DepthBlendingScale;
	Rx::LFR::Params::ECudaCompute::PreProc_Demosaic_B*/
	//Rx::LFR::CCudaCompute::Compute_PreProcess
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