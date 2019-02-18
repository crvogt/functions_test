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
	try
	{
		// if (argc != 2)
		// {
			// printf("Please provide the full file name of a ray image as the first command line argument.\n");
			// printf("Press any key to end program...\n");
			// _getch();
			// return 0;
		// }

		// Construct path to ray image
		//Rx::CRxString sxFile = "C:\\Users\\carson\\Desktop\\raytrix_api_tests\\rx_img.ray";
		Rx::CRxString sxFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\arm.ray";


		//Variables used for saving
		Rx::CRxString sxFile2;
		Rx::FileIO::CImage xImageFile;
		// Rx::CRxString sxFile = argv[1];

		/************************************************************************/
		/* Initialize and Prepare                                               */
		/************************************************************************/

		// Initialize CLUVizTool
		printf("Initializing CLUVizTool...\n");
		CLUViz::Tool::Init();

		// Create an image view
		printf("Creating image view window...\n");
		int iHandle;
		CLUViz::Tool::CreateViewImage(iHandle, 0, 0, 1000, 800, "");

		// Authenticate MGPU runtime
		printf("Authenticate LFR...\n");
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
		
		//Rx::LFR::CCalibration inputCalib = xInputImage.GetCalibration();
		xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned)Rx::Interop::Runtime28::EDataType::UByte);

		// Upload the image as the new raw image of all further CUDA computations
		printf("Uploading image to cuda compute instance...\n");
		xCudaCompute.UploadRawImage(xInputImage);

		// Get the image access interface. This interface allows:
		Rx::LFR::ICudaDataImages* pxImages = static_cast<Rx::LFR::ICudaDataImages*>(xCudaCompute.GetInterface(Rx::LFR::Interfaces::ECudaCompute::Images));

		printf("Starting image processing...\n");
		printf("\n");

		/************************************************************************/
		/* Image Processing                                                     */
		/************************************************************************/

		/************************************************************************/
		/* Processed Normalized                                                 */
		/************************************************************************/

		//Show raw light field image
		printf("Displaying raw light field image...\n");
		CLUViz::Tool::ViewSetImage(iHandle, &xInputImage);
		printf("Press any key...\n");
		printf("\n");
		_getch();
		//printf("Saving raw image...\n");
		//sxFile2 = "rx_Raw.png";
		//xImageFile.Write(&xInputImage, sxFile2);

		// Pre-process raw light field image before calling any processing functions
		printf("Pre-processing light field image...\n");
		xCudaCompute.Compute_PreProcess();

		// Get processed normalized image from CUDA device
		printf("Download image from CUDA device...\n");
		Rx::CRxImage xOutputImage;
		pxImages->Download(Rx::LFR::EImage::Processed_Normalized, &xOutputImage);
		Rx::FileIO::CImage saveImg;
		//saveImg.Write(&xOutputImage, "C:\\Users\\carson\\Desktop\\gray_to_png\\test_eh.png");
		// Display the image
		sxFile2 = "C:\\Users\\carson\\Desktop\\gray_to_png\\dval2.png";
		//xImageFile.Write(&xOutputImage, sxFile2);
		CLUViz::Tool::ViewSetImage(iHandle, &xOutputImage);

		// Wait for user to press any key.
		printf("Press any key...\n");
		printf("\n");
		_getch();
		//printf("Saving processed image...\n");
		//sxFile2 = "rx_Processed.png";
		//xImageFile.Write(&xOutputImage, sxFile2);

		/************************************************************************/
		/* Grid				                                                    */
		/************************************************************************/

		// Draw grid
		printf("Computing grid...\n");
		xCudaCompute.Compute_Grid();

		// Get grid image from CUDA device
		printf("Download image from CUDA device...\n");
		pxImages->Download(Rx::LFR::EImage::Grid, &xOutputImage);

		// Display the image
		CLUViz::Tool::ViewSetImage(iHandle, &xOutputImage);

		// Wait for user to press any key.
		printf("Press any key...\n");
		printf("\n");
		_getch();

		/************************************************************************/
		/* Refocus				                                                */
		/************************************************************************/
		double depthVal = 0;
		//Rx::CRxString sxFile2;
		//Rx::FileIO::CImage xImageFile;
		//for(int i = 0; i < 10; i++){
		//depthVal = 0.1;
		// Focus the image on 50% depth range
		printf("Focusing on calculated scene depth...");
		xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Focus_RelativeFocusPlane, depthVal);
		xCudaCompute.Compute_RefocusBasic();

		// Get refocus image from CUDA device
		printf("Download image from CUDA device...\n");
		pxImages->Download(Rx::LFR::EImage::RefocusBasic, &xOutputImage);

		// Display the image
		CLUViz::Tool::ViewSetImage(iHandle, &xOutputImage);

		// Save image
		sxFile2 = "C:\\Users\\carson\\Desktop\\gray_to_png\\rx_Focused.png";
		printf("Saving focused image as '%s'...\n", sxFile2.ToCString());
		xImageFile.Write(&xOutputImage, sxFile2);

		// Wait for user to press any key.
		printf("Press any key...\n");
		printf("\n");
		//std::cout << i << std::endl;
		_getch();
		//sxFile2 = "C:\\Users\\carson\\Desktop\\gray_to_png\\dval2.png";
		//xImageFile.Write(&xOutputImage, sxFile2);
		//}

		/************************************************************************/
		/*Get Grid Positions*/
		/*************************************************************************/
		Rx::CRxArray2DDouble ca2D;
		bool getMLAGrid = true;
		Rx::LFR::CCalibration &testValue(xInputImage.GetCalibration());
		testValue.GetGridData(ca2D, getMLAGrid);
		//std::cout << "Should be address for ca2D\n";
		std::cout << "GetElementSize: " << ca2D.GetElementSize() << std::endl;
		std::size_t rows, cols;
		ca2D.GetSize(rows, cols);
		std::cout << "rows: " << rows << " cols: " << cols << std::endl;


		Rx::CRxArray2DDouble::TValue *eh = ca2D.GetDataPtr();
		std::cout << "getting value of DataPtr: " << *eh << std::endl; 
		std::cout << "address of DataPtr: " << eh << std::endl;
		
		//std::cout << eh[8759][0];
		std::cout <<"IsValid?: " << ca2D.IsValid() << std::endl;
		//ca2D.Reset();
		//ca2D.GetSize(rows, cols);
		//std::cout << "Size after reset: rows: " << rows << " cols: " << cols << std::endl;
		std::ofstream camOutDetails;
		std::string fileName = "mxa_details.txt";

		camOutDetails.open(fileName);
		for(int i = 0; i < rows; i++) {
			camOutDetails << ca2D(i, 0) << ", "
				<< ca2D(i, 1) << ", "
				<< ca2D(i, 2) << ", "
				<< ca2D(i, 3) << "\n";
		}
		camOutDetails.close();
		//for (int i = 0; i < rows; i++) {
			//std::cout << "X: " << ca2D(i, 0) << " Y: " << ca2D(i,1) << std::endl;
		//}
		//while (true) {}

		/************************************************************************/
		/* Depth				                                                */
		/************************************************************************/
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

		// Save image with the exporter
		sxFile2 = "rx_Depth.png";
		printf("Saving depth image as '%s'...\n", sxFile2.ToCString());
		xImageFile.Write(&xOutputImage, sxFile2);

		// Finalizes the light field runtime and ends Cuda --> Finalizes all resources
		Rx::LFR::CLightFieldRuntime::End();

		// The example is finished
		printf("finished.\n");

		// Wait for user to press any key.
		printf("Press any key...\n");
		_getch();
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
