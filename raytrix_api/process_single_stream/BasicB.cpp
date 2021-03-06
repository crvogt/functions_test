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
#include <chrono>
#include <thread>
#include <iomanip>

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

using std::chrono::milliseconds;
using std::this_thread::sleep_for;

int main(int argc, char* argv[]){
	try {

		std::string rays_location;
		std::string proc_type;
		int num_streams = 0;

		if (argc < 1){
			std::cout << "rays_location, proc_type\n";
			return 0;
		}
		else{
			rays_location = std::string(argv[1]);
			proc_type = std::string(argv[2]);
			num_streams = std::stoi(std::string(argv[3]));
		}
		for (int seq_it = 0; seq_it < num_streams; seq_it++) {
			// Autheniticate MGPU runtime
			printf("Authenticate LFR...\n");
			Rx::LFR::CLightFieldRuntime::Authenticate();

			// Enumerate allCUDA devices at the beginning
			Rx::LFR::CCuda::EnumerateCudaDevices();

			Rx::CRxString rays_file;
			rays_file += rays_location.c_str();
			rays_file += seq_it;
			rays_file += "\\";
			rays_file += "0.rays";
			//"E:\\dual_exp\\video_one\\cam_zero\\0.rays";

			Rx::CRxString cam_0_write;
			cam_0_write += rays_location.c_str();
			cam_0_write += seq_it;
			cam_0_write += "\\";
			//cam_0_write += "0\\";

			unsigned int uFrameBufferCount = 2;

			Rx::LFR::CSeqFileReader read_seq;

			std::cout << "opening read_seq: " << std::endl;
			read_seq.Open(rays_file, uFrameBufferCount);

			std::cout << "file size: " << read_seq.GetFileSize();
			std::cout << "\nframe count: " << read_seq.GetFrameCount() << std::endl;

			Rx::LFR::CRayImage xInputImage;
			Rx::LFR::CCudaCompute xCudaCompute;
			Rx::CRxImage xOutputImage;

			read_seq.StartReading(xInputImage);

			int frameCount = 0;
			Rx::FileIO::CImage saveImg;

			xCudaCompute.SetCudaDevice(Rx::LFR::CCuda::GetDevice(Rx::LFR::CCuda::GetDeviceCount() - 1));

			int cam_0_sum = 0;

			// Get the image access interface. This interface allows:
			Rx::LFR::ICudaDataImages* pxImages = static_cast<Rx::LFR::ICudaDataImages*>(xCudaCompute.GetInterface(Rx::LFR::Interfaces::ECudaCompute::Images));

			std::ofstream time_vals;
			std::string fileName = rays_location.c_str();
			if (proc_type == "timestamp"){
				fileName += std::to_string(seq_it);
				fileName += "\\timestamps.txt";

				time_vals.open(fileName);
			}

			while (frameCount < read_seq.GetFrameCount() - 1) {
				//temp_string

				//saveImg.write() //See example in another file, b or something...
				// Assign the CUDA device and the calibration
				printf("Selecting CUDA device...\n");
				//Rx::LFR::CCudaCompute xCudaCompute;
				xCudaCompute.ApplyCalibration(xInputImage.GetCalibration(), true);
				xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DataType, (unsigned)Rx::Interop::Runtime28::EDataType::UByte);

				// Upload the image as the new raw image of all further CUDA computations
				//printf("Uploading image to cuda compute instance...\n");
				xCudaCompute.UploadRawImage(xInputImage);

				if (proc_type == "raw") {
					pxImages->Download(Rx::LFR::EImage::Raw, &xOutputImage);
				}
				else if (proc_type == "timestamp") {
					pxImages->Download(Rx::LFR::EImage::Raw, &xOutputImage);
				}
				else if (proc_type == "processed") {
					xCudaCompute.Compute_PreProcess();
					pxImages->Download(Rx::LFR::EImage::Processed_Normalized, &xOutputImage);
				}
				else if (proc_type == "ray_depth") {
					xCudaCompute.Compute_PreProcess();
					xCudaCompute.Compute_DepthRay();
					pxImages->Download(Rx::LFR::EImage::DepthRay, &xOutputImage);

				}
				else if (proc_type == "total_focus") {
					xCudaCompute.Compute_PreProcess();
					xCudaCompute.Compute_DepthRay();
					xCudaCompute.Compute_DepthMap();
					xCudaCompute.Compute_TotalFocus();
					pxImages->Download(Rx::LFR::EImage::TotalFocus_View_Object_Pinhole, &xOutputImage);
				}
				else if (proc_type == "dm") {
					xCudaCompute.Compute_PreProcess();

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
					
					xCudaCompute.Compute_DepthRay();
					xCudaCompute.Compute_DepthMap(Rx::LF::ESpace::View_Object_Pinhole);
					xCudaCompute.Compute_Depth3D();
					xCudaCompute.Compute_DepthColorCode(Rx::LF::ESpace::View_Object_Pinhole);
					pxImages->Download(Rx::LFR::EImage::DepthMapColored_View_Object_Pinhole, &xOutputImage);
				}
				else if (proc_type == "dm_raw") {
					xCudaCompute.Compute_PreProcess();

					// Set Pre-Process Parameters
					xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::PreProc_DenoiseNLM_Enable, 0U);
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
					xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Enabled, 0U);
					xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_IterCnt, 4U);
					xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_IterSize, 1U);
					xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Complete, 1U);

					// Depth Fill Bilateral filter
					xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_Enabled, 0U);
					xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_FilterRadius, 5U);
					xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_Edge, 0.1);
					xCudaCompute.GetParams().SetValue(Rx::LFR::Params::ECudaCompute::Depth_Fill_Bilateral_Range, 5.0);

					xCudaCompute.Compute_DepthRay();
					xCudaCompute.Compute_DepthMap(Rx::LF::ESpace::View_Object_Pinhole);
					xCudaCompute.Compute_Depth3D();
					xCudaCompute.Compute_DepthColorCode(Rx::LF::ESpace::View_Object_Pinhole);
					pxImages->Download(Rx::LFR::EImage::DepthMapColored_View_Object_Pinhole, &xOutputImage);
				}

				Rx::CRxString temp_string;
				
				std::cout << "proc_type: " << proc_type << std::endl;
				if (proc_type != "ray_depth" && proc_type != "timestamp") {
					temp_string += cam_0_write;
					temp_string += proc_type.c_str();
					temp_string += "\\";
					temp_string += cam_0_sum;
					temp_string += "_";
					temp_string += xInputImage.GetTimestamp();
					temp_string += ".png";
					//std::cout << xInputImage.GetTimestamp() << std::endl;
					//std::printf("time: %f\n", xInputImage.GetTimestamp());
					saveImg.Write(&xOutputImage, temp_string);

					cam_0_sum++;

				}
				
				else if (proc_type == "ray_depth") {
					temp_string += cam_0_write;
					temp_string += proc_type.c_str();
					temp_string += "\\";
					//temp_string += cam_0_sum;
					//temp_string += "_";
					temp_string += xInputImage.GetTimestamp();
					temp_string += ".tiff";
					//std::printf("time: %f\n", xInputImage.GetTimestamp());

					saveImg.Write(&xOutputImage, temp_string);

					cam_0_sum++;

				}
				else if (proc_type == "timestamp") {
					std::cout << "writing timestampe... " << std::endl;
					time_vals << std::setprecision(12) << xInputImage.GetTimestamp() << "\n";
				}

				frameCount++;
				std::cout << "frameCount: " << frameCount << std::endl;

				//Let's us iterate through frames
				read_seq.SetFrameIndex(frameCount);
				read_seq.ReadFrame(xInputImage);
				//sleep_for(milliseconds(100));

			}

			std::cout << "cam 0: " << cam_0_sum << std::endl;
			read_seq.Close();
			if (proc_type == "timestamp") {
				time_vals.close();
			}
		}
		return 0;
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

}
