/*
This file should go through all of the raw images and convert them to 
.ray files that can work...

Refer to new_ray_from_raw
*/

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

int main(int argc, char* argv[]){
	try{
		Rx::CRxString sxRayFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\arm.ray";

		// Initialize CLUVizTool
		printf("Initializing CLUVizTool...\n");
		CLUViz::Tool::Init();
		printf("Creating image view window...\n");
		int iView = 0;
		CLUViz::Tool::CreateViewImage(iView, 0, 0, 1000, 800, "");

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

		// Bind the loaded ray image. This copies the ray image to the CUDA device.
		Rx::LFR::CApiLF::RxRayBind(uImgID);

		// Get normalized image from CUDA device
		Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Raw, xRayImage);
		// Display the image
		CLUViz::Tool::ViewSetImage(iView, &xRayImage);

		//// Wait for user to press any key.
		printf("Press any key...\n");
		_getch();

		// Start importing the .png files
		Rx::FileIO::CImage xImageFile;
		Rx::CRxString sxRawPngFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\5_orig_low.png";
		Rx::CRxImage xRawImage;
		Rx::CRxImage xImgLum, xImgBayer;
		Rx::CRxImage imageLumGray;
		Rx::CRxString sxGrayPngFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\b_gray.png";
		Rx::CRxImage xGrayImage;

		// Load raw image
		printf("Loading raw image '%s'...\n", sxRawPngFile.ToCString());
		xImageFile.Read(&xImgLum, sxRawPngFile);
		xImgBayer.Create(xImgLum.GetFormat().m_iWidth, xImgLum.GetFormat().m_iHeight, Rx::Interop::Runtime28::EPixelType::BayerGB, Rx::Interop::Runtime28::EDataType::UByte, xImgLum.GetDataPtr());
	
		CLUViz::Tool::ViewSetImage(iView, &xImgBayer);
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
		Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Raw, xImgBayer);
		xImgBayer.Destroy();


		Rx::LFR::CApiLF::RxSetImage(Rx::LFR::EImage::ID::Gray, xGrayImage);
		xGrayImage.Destroy();
		
		Rx::CRxString newRayFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\newTestRay.ray";
 
		Rx::LFR::CApiLF::RxRaySave(newRayFile, true);

		// Get normalized image from CUDA device
		Rx::LFR::CApiLF::RxGetImage(Rx::LFR::EImage::ID::Processed_Normalized, xRayImage);
		
		Rx::FileIO::CImage writeImg;
		Rx::CRxString writeOut = "C:\\Users\\carson\\Desktop\\gray_to_png\\check.png";
		writeImg.Write(&xRayImage, writeOut);
	}
	catch (Rx::CRxException& ex){
			printf("Exception occured:\n%s\n\n", ex.ToString(true).ToCString());
			printf("Press any key to end program...\n");
			_getch();
			return -1;
		}
	catch (Rx::IException31& ex){
			printf("Exception occured:\n%s\n\n", ex.GetMessageText());
			printf("Press any key to end program...\n");
			_getch();
			return -1;
		}
	return 0;
}