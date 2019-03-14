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
	
		Rx::CRxString rays_file = "E:\\dual_exp\\video_one\\cam_zero\\0.rays";
		Rx::CRxString cam_0_write = "E:\\dual_exp\\video_one\\cam_zero\\0\\";
		Rx::CRxString cam_1_write = "E:\\dual_exp\\video_one\\cam_zero\\1\\";
		Rx::CRxString temp_string;
		unsigned int uFrameBufferCount = 2;
		
		Rx::LFR::CSeqFileReader read_seq;
		
		std::cout << "opening read_seq: " << std::endl;
		read_seq.Open(rays_file, uFrameBufferCount);

		std::cout << "file size: " << read_seq.GetFileSize();
		std::cout << "\nframe count: " << read_seq.GetFrameCount() << std::endl;
		
		Rx::LFR::CRayImage xInputImage;
		Rx::LFR::CCudaCompute xCudaCompute;

		read_seq.StartReading(xInputImage);
		int frameCount = 0;
		Rx::FileIO::CImage saveImg;
		xCudaCompute.SetCudaDevice(Rx::LFR::CCuda::GetDevice(Rx::LFR::CCuda::GetDeviceCount() - 1));

		while(frameCount < read_seq.GetFrameCount()){
			//temp_string
			
			//saveImg.write() //See example in another file, b or something...
			// Assign the CUDA device and the calibration
			printf("Selecting CUDA device...\n");
			//Rx::LFR::CCudaCompute xCudaCompute;
			xCudaCompute.ApplyCalibration(xInputImage.GetCalibration(), true);
			xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned)Rx::Interop::Runtime28::EDataType::UByte);
			std::cout << "inputID: " << xInputImage.GetID() << std::endl;
			// Upload the image as the new raw image of all further CUDA computations
			//printf("Uploading image to cuda compute instance...\n");
			xCudaCompute.UploadRawImage(xInputImage);

			// Get the image access interface. This interface allows:
			Rx::LFR::ICudaDataImages* pxImages = static_cast<Rx::LFR::ICudaDataImages*>(xCudaCompute.GetInterface(Rx::LFR::Interfaces::ECudaCompute::Images));

			//saveImg.Write(&xOutputImage, wImgFile);

			frameCount++;

			//Let's us iterate through frames
			read_seq.SetFrameIndex(frameCount);
			read_seq.ReadFrame(xInputImage);
		}
		return 0;
}
