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
#include "Rx.LFR\SeqFileWriter.h"

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
		// Construct path to ray image
		//Rx::CRxString sxFile = "C:\\Users\\carson\\Desktop\\raytrix_api_tests\\rx_img.ray";
		Rx::CRxString sxFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\Non_Demo.ray";
		Rx::CRxString testSeqFile = "C:\\Users\\carson\\Desktop\\gray_to_png\\seq_test_1.rays";
		
		//Variables used for saving
		Rx::FileIO::CImage xImageFile;

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
		xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned)Rx::Interop::Runtime28::EDataType::UByte);

		// Upload the image as the new raw image of all further CUDA computations
		printf("Uploading image to cuda compute instance...\n");
		xCudaCompute.UploadRawImage(xInputImage);

		// Get the image access interface. This interface allows:
		Rx::LFR::ICudaDataImages* pxImages = static_cast<Rx::LFR::ICudaDataImages*>(xCudaCompute.GetInterface(Rx::LFR::Interfaces::ECudaCompute::Images));


		//Show raw light field image
		printf("Displaying raw light field image...\n");
		CLUViz::Tool::ViewSetImage(iHandle, &xInputImage);
		printf("Press any key...\n");
		printf("\n");
		_getch();

		// Wait for user to press any key.
		printf("Press any key...\n");
		printf("\n");
		_getch();
		xInputImage.
		std::cout << "create seqwriter\n";
		Rx::LFR::CSeqFileWriter SeqWriter;
		unsigned int bufCount = 2U;
		unsigned int doubleShotMode = 2U;
		SeqWriter.Open(testSeqFile, bufCount);
		SeqWriter.StartWriting(xInputImage.GetFormat(), xInputImage.GetCalibration(), xInputImage.GetMetaData(), doubleShotMode);
		std::cout << "Enter for loop\n";
		for (int i = 0; i < 100; i++) {
			SeqWriter.WriteFrame(xInputImage);
			std::cout << "i: " << i << std::endl;
		}
		SeqWriter.Close();
		
	
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
