///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// COPYRIGHT (C) 2016 RAYTRIX GMBH. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///************************************************************************/
///*  THIS EXAMPLE DEMONSTRATES:                                          */
///*      - WORKING WITH AN IMAGE.                                        */
///*      - PROCESSING IMAGE                                              */
///*      - SETTING PARAMETER                                             */
///*      - DISPLAYING RESULTS                                            */
///************************************************************************/
//
//#INCLUDE <CONIO.H>
//#INCLUDE <IOSTREAM>
//#INCLUDE <FSTREAM>
//#INCLUDE <STRING>
//
//#INCLUDE "RX.CORE\RXEXCEPTION.H"
//#INCLUDE "RX.CLUVIZ.CORE.CLUVIZTOOL\CVCLUVIZTOOL.H"
//#INCLUDE "RX.FILEIO\RX.FILEIO.IMAGE.H"
//
//#INCLUDE "RX.LFR\LIGHTFIELDRUNTIME.H"
//#INCLUDE "RX.LFR\CUDA.H"
//#INCLUDE "RX.LFR\CUDACOMPUTE.H"
//#INCLUDE "RX.LFR\RAYFILEREADER.H"
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// <SUMMARY>
///// 	MAIN ENTRY-POINT FOR THIS APPLICATION.
///// </SUMMARY>
/////
///// <PARAM NAME="ARGC"> NUMBER OF COMMAND-LINE ARGUMENTS. </PARAM>
///// <PARAM NAME="ARGV"> ARRAY OF COMMAND-LINE ARGUMENT STRINGS. </PARAM>
/////
///// <RETURNS> EXIT-CODE FOR THE PROCESS - 0 FOR SUCCESS, ELSE AN ERROR CODE. </RETURNS>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INT MAIN(INT ARGC, CHAR* ARGV[])
//{
//	TRY
//	{
//		RX::CRXSTRING SXFILE = "C:\\USERS\\CVOGT\\DESKTOP\\GRAY_TO_PNG\\0034035116\\PROC_TEST\\PLANT.RAY";
//		RX::CRXSTRING WRITEOUT = "C:\\USERS\\CVOGT\\DESKTOP\\GRAY_TO_PNG\\0034035116\\PROC_TEST\\PLANT_PROC_TEST.PNG";
//
//		//VARIABLES USED FOR SAVING
//		RX::CRXSTRING SXFILE2;
//		RX::FILEIO::CIMAGE XIMAGEFILE;
//
//		// AUTHENTICATE MGPU RUNTIME
//		PRINTF("AUTHENTICATE LFR...\N");
//		RX::LFR::CLIGHTFIELDRUNTIME::AUTHENTICATE();
//
//		// ENUMERATE ALL CUDA DEVICES AT THE BEGINNING
//		RX::LFR::CCUDA::ENUMERATECUDADEVICES();
//
//		// LOAD RAY IMAGE
//		PRINTF("LOADING IMAGE '%S'...\N", SXFILE.TOCSTRING());
//		RX::LFR::CRAYIMAGE XINPUTIMAGE;
//		RX::LFR::CRAYFILEREADER::READ(SXFILE, XINPUTIMAGE);
//
//		// ASSIGN THE CUDA DEVICE AND THE CALIBRATION
//		PRINTF("SELECTING CUDA DEVICE...\N");
//		RX::LFR::CCUDACOMPUTE XCUDACOMPUTE;
//		XCUDACOMPUTE.SETCUDADEVICE(RX::LFR::CCUDA::GETDEVICE(RX::LFR::CCUDA::GETDEVICECOUNT() - 1));
//		XCUDACOMPUTE.APPLYCALIBRATION(XINPUTIMAGE.GETCALIBRATION(), TRUE);
//
//		//RX::LFR::CCALIBRATION INPUTCALIB = XINPUTIMAGE.GETCALIBRATION();
//		XCUDACOMPUTE.GETPARAMS().SETVALUE(RX::LFR::PARAMS::ECUDACOMPUTE::PREPROC_STD_ENABLE, (UNSIGNED)0);
//		XCUDACOMPUTE.GETPARAMS().SETVALUE(RX::LFR::PARAMS::ECUDACOMPUTE::PREPROC_DATATYPE, (UNSIGNED)RX::INTEROP::RUNTIME28::EDATATYPE::UBYTE);
//
//		// UPLOAD THE IMAGE AS THE NEW RAW IMAGE OF ALL FURTHER CUDA COMPUTATIONS
//		PRINTF("UPLOADING IMAGE TO CUDA COMPUTE INSTANCE...\N");
//		XCUDACOMPUTE.UPLOADRAWIMAGE(XINPUTIMAGE);
//
//		// GET THE IMAGE ACCESS INTERFACE. THIS INTERFACE ALLOWS:
//		RX::LFR::ICUDADATAIMAGES* PXIMAGES = STATIC_CAST<RX::LFR::ICUDADATAIMAGES*>(XCUDACOMPUTE.GETINTERFACE(RX::LFR::INTERFACES::ECUDACOMPUTE::IMAGES));
//
//		// PRE-PROCESS RAW LIGHT FIELD IMAGE BEFORE CALLING ANY PROCESSING FUNCTIONS
//		PRINTF("PRE-PROCESSING LIGHT FIELD IMAGE...\N");
//	
//		//XCUDACOMPUTE.GETPARAMS().SETVALUE(RX::LFR::PARAMS::ECUDACOMPUTE::PREPROC_STD_ENABLE, (UNSIGNED)0);
//
//		//XCUDACOMPUTE
//		XCUDACOMPUTE.COMPUTE_PREPROCESS();
//
//		// GET PROCESSED NORMALIZED IMAGE FROM CUDA DEVICE
//		PRINTF("DOWNLOAD IMAGE FROM CUDA DEVICE...\N");
//		RX::CRXIMAGE XOUTPUTIMAGE;
//		PXIMAGES->DOWNLOAD(RX::LFR::EIMAGE::PROCESSED_NORMALIZED, &XOUTPUTIMAGE);
//		RX::FILEIO::CIMAGE WRITEIMG;
//		WRITEIMG.WRITE(&XOUTPUTIMAGE, WRITEOUT);
//		
//	}
//	CATCH (RX::CRXEXCEPTION& EX)
//	{
//		PRINTF("EXCEPTION OCCURED:\N%S\N\N", EX.TOSTRING(TRUE).TOCSTRING());
//		PRINTF("PRESS ANY KEY TO END PROGRAM...\N");
//		_GETCH();
//		RETURN -1;
//	}
//	CATCH (RX::IEXCEPTION31& EX)
//	{
//		PRINTF("EXCEPTION OCCURED:\N%S\N\N", EX.GETMESSAGETEXT());
//		PRINTF("PRESS ANY KEY TO END PROGRAM...\N");
//		_GETCH();
//		RETURN -1;
//	}
//
//	RETURN 0;
//}



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
	try {
		
		Rx::CRxString sxRayFile = "C:\\Users\\cvogt\\Desktop\\gray_to_png\\0034035116\\proc_test\\plant.ray";
		Rx::CRxString sxGrayPngFile = "C:\\Users\\cvogt\\Desktop\\gray_to_png\\0034035116\\proc_test\\gray.png";
		Rx::CRxString sxRawPngFile = "C:\\Users\\cvogt\\Desktop\\gray_to_png\\0034035116\\proc_test\\plant_proc.png";
		Rx::CRxString writeOut = "C:\\Users\\cvogt\\Desktop\\gray_to_png\\0034035116\\proc_test\\plant_proc_test.png";

		// Ray image
		Rx::CRxImage xRayImage;

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
		
		// Start importing the .png files
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

		// Now apply the raw image and the gray image to the loaded ray image.
		//Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Processed_Normalized, xImgBayer);
		//xImgBayer.Destroy();

		Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Gray, xGrayImage);
		xGrayImage.Destroy();

		// Process image with no white image
		printf("Preprocessing...\n");
		//Rx::LFR::CApiLF::RxGetPar().R
		//Rx::LFR::CApiLF::RxSetPar(Rx::LFR::Params::ECudaCompute::PreProc_Demosaic_Enable, 0);
		
		Rx::LFR::CApiLF::RxPreProcess();
		Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Processed_Normalized, xImgBayer);
		xImgBayer.Destroy();

		Rx::LFR::CApiLF::RxRaySave(sxRayFile, true);
		// Get normalized image from CUDA device
		std::cout << "Getting preprocessed lf\n";
		//Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Processed_Normalized, xRayImage);

		Rx::FileIO::CImage writeImg;
		writeImg.Write(&xRayImage, writeOut);
		
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