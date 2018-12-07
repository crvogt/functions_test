/*
This file should allow us to go from LF video to individual
raw images

Taking in .rays, outputing a raw.png for each frame to a folder 
that can be easily read later
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
#include "Rx.LFR\ApiLF.h"
#include "Rx.LFR\Enums.Values.h"
#include "Rx.LFR\SeqFileReader.h"

int main(int argc, char* argv[]){
		// Setup cuda stuff...
		printf("Initializing CluVizTool...\n");
		CLUViz::Tool::Init();

		// Autheniticate MGPU runtime
		printf("Authenticate LFR...\n");
		Rx::LFR::CLightFieldRuntime::Authenticate();

		// Enumerate allCUDA devices at the beginning
		Rx::LFR::CCuda::EnumerateCudaDevices();
		
		Rx::CRxString sxFile = "C:\\Users\\carson\\Desktop\\raytrix_gp_experiments\\Experiment3\\main_ray_3.rays";
		Rx::CRxString myString = "C:\\Users\\carson\\Desktop\\raytrix_gp_experiments\\Experiment3\\raytrixImages\\";
		Rx::CRxString wImgFile;
		unsigned int uFrameBufferCount = 2;
		
		std::cout << "File location: " << sxFile.ToCString() << std::endl;
		
		Rx::LFR::CSeqFileReader readObj;
		
		readObj.Open(sxFile, uFrameBufferCount);

		std::cout << "file size: " << readObj.GetFileSize();
		std::cout << "\nframe count: " << readObj.GetFrameCount() << std::endl;
		
		Rx::LFR::CRayImage xInputImage;
		Rx::LFR::CCudaCompute xCudaCompute;
		
		// Create an image view
		printf("Creating image view window...\n");
		int iHandle;
		CLUViz::Tool::CreateViewImage(iHandle, 0, 0, 1000, 800, "");

		readObj.StartReading(xInputImage);
		int frameCount = 0;
		Rx::FileIO::CImage saveImg;
		while(frameCount < readObj.GetFrameCount()){
			myString += frameCount;
			myString += ".png";
			wImgFile = myString;
			
			//saveImg.write() //See example in another file, b or something...
			// Assign the CUDA device and the calibration
			printf("Selecting CUDA device...\n");
			//Rx::LFR::CCudaCompute xCudaCompute;
			xCudaCompute.SetCudaDevice(Rx::LFR::CCuda::GetDevice(Rx::LFR::CCuda::GetDeviceCount() - 1));
			xCudaCompute.ApplyCalibration(xInputImage.GetCalibration(), true);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned)Rx::Interop::Runtime28::EDataType::UByte);

			// Upload the image as the new raw image of all further CUDA computations
			printf("Uploading image to cuda compute instance...\n");
			xCudaCompute.UploadRawImage(xInputImage);

			// Get the image access interface. This interface allows:
			Rx::LFR::ICudaDataImages* pxImages = static_cast<Rx::LFR::ICudaDataImages*>(xCudaCompute.GetInterface(Rx::LFR::Interfaces::ECudaCompute::Images));

			saveImg.Write(&xOutputImage, wImgFile);

			frameCount++;

			//Let's us iterate through frames
			readObj.SetFrameIndex(frameCount);
			readObj.ReadFrame(xInputImage);
		}
		return 0;
}
