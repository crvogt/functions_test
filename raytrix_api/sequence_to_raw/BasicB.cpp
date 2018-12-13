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
	try {

		int scene_num = 4;

		// Initialize CLUVizTool
		//printf("Initializing CluVizTool...\n");
		//CLUViz::Tool::Init();

		// Autheniticate MGPU runtime
		printf("Authenticate LFR...\n");
		Rx::LFR::CLightFieldRuntime::Authenticate();

		// Enumerate allCUDA devices at the beginning
		Rx::LFR::CCuda::EnumerateCudaDevices();

		Rx::CRxString sxFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\raytrix_iccp\\video\\";
		sxFile += scene_num;
		sxFile += "\\s6.rays";
		Rx::CRxString wImgFile, dImgFile;
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
		//printf("Creating image view window...\n");
		//int iHandle;
		//CLUViz::Tool::CreateViewImage(iHandle, 0, 0, 1000, 800, "");

		readObj.StartReading(xInputImage);
		unsigned int iter = 0;
		int moveVal = 0;
		int frameCount = 0;
		Rx::FileIO::CImage saveImg;
		while (iter < readObj.GetFrameCount()) {
			std::cout << "On: " << iter << " of " << readObj.GetFrameCount() << std::endl;
			Rx::CRxString myString = "C:\\Users\\carson\\Desktop\\low_light_video\\";
			myString += scene_num;
			myString += "\\";
			myString += frameCount;
			myString += ".png";		
			wImgFile = myString;

			// Assign the CUDA device and the calibration
			printf("Selecting CUDA device...\n");
			xCudaCompute.SetCudaDevice(Rx::LFR::CCuda::GetDevice(Rx::LFR::CCuda::GetDeviceCount() - 1));
			xCudaCompute.ApplyCalibration(xInputImage.GetCalibration(), true);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned)Rx::Interop::Runtime28::EDataType::UByte);

			// Upload the image as the new raw image of all further CUDA computations
			printf("Uploading image to cuda compute instance...\n");
			xCudaCompute.UploadRawImage(xInputImage);

			//Show raw light field image
			/*
			printf("Displaying raw light field image...\n");
			CLUViz::Tool::ViewSetImage(iHandle, &xInputImage);
			printf("Press any key...\n");
			printf("\n");
			_getch();
			*/

			saveImg.Write(&xInputImage, wImgFile);

			//Let's us iterate through frames
			readObj.SetFrameIndex(iter + 1);
			readObj.ReadFrame(xInputImage);

			iter++;
			frameCount++;
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
