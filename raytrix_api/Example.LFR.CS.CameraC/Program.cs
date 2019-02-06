/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Raytrix GmbH. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  This example demonstrates:                                          */
/*      - Working with one camera with multiple GPUs  */
/************************************************************************/

using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: Example.LFR.CS.BasicD
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Example.LFR.CS.CameraC
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///     Multiple Cameras one GPU synchronous.
	/// </summary>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Example
	{
		/// <summary> The CUDA compute class. </summary>
		Rx.LFR.Net.CudaCompute[] m_pxCudaCompute;
		/// <summary> The visualization handles. </summary>
		int m_iHandle;
		/// <summary> The camera server class that is able to find attached cameras. </summary>
		Rx.LFR.Net.CameraServer m_xCamServer;
		/// <summary> The camera buffers. </summary>
		Rx.LFR.Net.ImageQueue m_xCamBuffer;
		/// <summary> The camera buffers. </summary>
		Rx.LFR.Net.ImageQueue m_xComputedBuffer;
		/// <summary> The threads. </summary>
		System.Threading.Thread[] m_xThreads;
		/// <summary> true to stop thread. </summary>
		bool m_bStopThread = false;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Executes the image captured action.
		/// </summary>
		///
		/// <param name="xConstImage"> The image. </param>
		/// <param name="uCamIdx">     The camera index. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void OnImageCaptured(Rx.LFR.Net.ConstImage xConstImage, uint uCameraIndex)
		{
			/************************************************************************/
			/* Image Captured                                                       */
			/************************************************************************/

			// ATTENTION:
			// All processing done in this callback would prevents the camera from capturing the next image.
			// Therefore it's advisable to BUFFER the image here and to process it in another thread.

			/************************************************************************/
			/* Write into buffer                                                    */
			/************************************************************************/
			if (!m_xCamBuffer.CopyIn(xConstImage))
			{
				// Buffer is full and overwrite is disabled
				// This is a lost frame
				return;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Process the image.
		/// </summary>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void ProcessImage(object uCudaDevice)
		{
			// As long as this application is not stopped
			while (!m_bStopThread)
			{
				try
				{
					// Wait for the image buffer to be not empty
					if (m_xCamBuffer.WaitForNotEmpty(1000))
					{
						Console.WriteLine("Buffer not empty");

						// Get the first image in the Queue
						Rx.Net.Image xImage = new Rx.Net.Image();
						if (!m_xCamBuffer.MoveOut(xImage))
						{
							// Wait again! This functions says that it waits until a frame is available
							continue;
						}

						Console.WriteLine("Getting Cuda Device with index {0}", (int) uCudaDevice);

						// Get the CUDA compute class for this camera
						Rx.LFR.Net.CudaCompute xCudaCompute = m_pxCudaCompute[(int) uCudaDevice];

						Console.WriteLine("Uploading image ...");

						// Upload the captured image as the new raw image of all further CUDA computations
						xCudaCompute.UploadRawImage(xImage);

						Console.WriteLine("Processing image ...");

						// Calculate the desired images
						xCudaCompute.Compute_PreProcess();
						xCudaCompute.Compute_RefocusBasic();
						xCudaCompute.Compute_DepthRay();
						xCudaCompute.Compute_DepthMap(Rx.LFR.Net.ESpace.View_Object_Pinhole);
						xCudaCompute.Compute_TotalFocus(Rx.LFR.Net.ESpace.View_Object_Pinhole);
						xCudaCompute.Compute_Depth3D();
						xCudaCompute.Compute_DepthColorCode(Rx.LFR.Net.ESpace.View_Object_Pinhole);

						// Get the image access interface. This interface allows:
						// * Download CUDA image into host memory
						// * Upload a host image to CUDA to overwrite a certain CUDA image
						// * Access to CUDA device pointer to do own CUDA image processing
						Rx.LFR.Net.ICudaDataImages xImages = (xCudaCompute.GetInterface(Rx.LFR.Net.Interfaces.ECudaCompute.Images)) as Rx.LFR.Net.ICudaDataImages;

						Console.WriteLine("Downloading image ...");

						using (Rx.Net.Image xImgDepthMapColor = new Rx.Net.Image())
						{
							// Download images into the host memory
							xImages.Download(Rx.LFR.Net.EImage.DepthMapColored_View_Object_Pinhole,  xImgDepthMapColor);

							// Move image into computed buffer
							m_xComputedBuffer.MoveIn(xImgDepthMapColor);
						}
					}
				}
				catch (Rx.Net.RxException ex)
				{
					Console.WriteLine("Exception");
					Console.WriteLine("\n\n\nOnImageCaptured Exception:\n\n\n{0}\n\n\n", ex.ToString(true));
					Environment.Exit(-1);
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Process the image.
		/// </summary>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void ShowImage()
		{
			// As long as this application is not stopped
			while (!m_bStopThread)
			{
				try
				{
					// Wait for the image buffer to be not empty
					if (m_xComputedBuffer.WaitForNotEmpty(1000))
					{
						Console.WriteLine("Computed image buffer not empty");

						// Get the first image in the Queue
						using (Rx.Net.Image xImage = new Rx.Net.Image())
						{
							if (!m_xComputedBuffer.MoveOut(xImage))
							{
								// Wait again! This functions says that it waits until a frame is available
								continue;
							}
							CLUViz.Net.Tool.ViewSetImage(m_iHandle, xImage);
						}
					}
				}
				catch (Rx.Net.RxException ex)
				{
					Console.WriteLine("Exception");
					Console.WriteLine("\n\n\nOnImageCaptured Exception:\n\n\n{0}\n\n\n", ex.ToString(true));
					Environment.Exit(-1);
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Runs this example.
		/// </summary>
		///
		/// <returns> The return code. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public int Run()
		{
			Console.WriteLine("Initializing visualization...");

			CLUViz.Net.Tool.Init();

			/************************************************************************/
			/* Authenticate LFR                                                     */
			/************************************************************************/
			Rx.LFR.Net.LightFieldRuntime.Authenticate();

			///  Initialize the calibration manager.
			Rx.LFR.Net.CalibrationManager.Initialize();

			// Enumerate all CUDA devices at the beginning
			Rx.LFR.Net.Cuda.EnumerateCudaDevices();

			uint uBufferSize = System.Convert.ToUInt32(5);
			bool bOverwrite  = false;

			System.Console.WriteLine("Please enter depth settings path: ");
			System.String xDepthSettingsPath = System.Console.ReadLine();
			if (!System.IO.File.Exists(xDepthSettingsPath))
			{
				System.Console.WriteLine("File does not exist!");
				return -1;
			}

			/************************************************************************/
			/* CUDA                                                                 */
			/************************************************************************/
			int iCudaDevices = Rx.LFR.Net.Cuda.GetDeviceCount();
			m_pxCudaCompute = new Rx.LFR.Net.CudaCompute[iCudaDevices];
			m_xThreads      = new System.Threading.Thread[iCudaDevices];

			Console.WriteLine("CUDA Devices");
			for (int iIdx = 0; iIdx < Rx.LFR.Net.Cuda.GetDeviceCount(); iIdx++)
			{
				Rx.LFR.Net.CudaDevice xCuda = Rx.LFR.Net.Cuda.GetDevice(iIdx);

				string sName;
				xCuda.GetParams().GetValue(Rx.LFR.Net.Params.ECudaDevice.Name, out sName);

				double dClockMHz;
				xCuda.GetParams().GetValue(Rx.LFR.Net.Params.ECudaDevice.ClockFrequencyMHz, out dClockMHz);

				double dGlobalMemMB;
				xCuda.GetParams().GetValue(Rx.LFR.Net.Params.ECudaDevice.TotalGlobalMemoryMB, out dGlobalMemMB);

				Console.WriteLine("{0}: {1}, Clock: {2} MHz, Memory: {3} MB", iIdx, sName, dClockMHz, dGlobalMemMB);
			}

			/************************************************************************/
			/* Find Cameras                                                         */
			/************************************************************************/
			Console.WriteLine("Find Cameras");

			// Add a status message callback if you are interested in status messages sent by the camera server while finding cameras
			m_xCamServer = new Rx.LFR.Net.CameraServer();

			// Start to find cameras. This is an synchronous call and we wait here until the find process has been finished
			m_xCamServer.FindCameras();

			// Quit the application if there is no camera
			if (m_xCamServer.GetCameraCount() == 0)
			{
				Console.Write("No camera found\n");
				return -1;
			}

			/************************************************************************/
			/* Start Cameras                                                        */
			/************************************************************************/
			Console.WriteLine("Start Cameras");
			int iAssignedCudaDevice = 0;

			/************************************************************************/
			/* Initialize Buffer                                                    */
			/************************************************************************/

			// Create buffer within the given size and with the given overwrite flag
			m_xCamBuffer = new Rx.LFR.Net.ImageQueue();
			m_xCamBuffer.Initialize(uBufferSize, bOverwrite);

			// Get the camera from our camera server
			Rx.LFR.Net.Camera xCamera = m_xCamServer.GetCamera(0);

			// Load the default calibration of the camera (and load the gray image too)
			Rx.LFR.Net.Calibration xDefaultCalibration = new Rx.LFR.Net.Calibration();
			Rx.LFR.Net.CalibrationManager.LoadDefaultCalibration(xDefaultCalibration, xCamera, true);

			// Open the camera. This prepares the communication with the camera and checks the connection of GigE cameras
			// This does NOT start the camera stream
			xCamera.Open();

			// Add a image captured callback. This method gets called for every captured camera image and more details are given there
			xCamera.ImageCaptured += OnImageCaptured;

			string sCudaName;
			(Rx.LFR.Net.Cuda.GetDevice((int) iAssignedCudaDevice)).GetParams().GetValue(Rx.LFR.Net.Params.ECudaDevice.Name, out sCudaName);

			// Create the visualization
			// If there is one image buffer per camera set the view caption to the camera name;
			string sCameraName = Rx.LFR.Net.CalibrationManager.GetCameraName(xCamera);
			m_iHandle = CLUViz.Net.Tool.CreateViewImage((int) 0, 0, 1000, 800, sCameraName);

			float fMin = 0.0f;
			float fMax = 0.0f;
			xCamera.GetPropertyRange(Rx.InteropNet.Runtime30.Camera.EProperty.Framerate, out fMin, out fMax);
			xCamera.SetProperty(Rx.InteropNet.Runtime30.Camera.EProperty.Framerate, fMax);
			Console.WriteLine("Setting Camera {0} to its max FPS: {1}", sCameraName, fMax);

			xCamera.GetPropertyRange(Rx.InteropNet.Runtime30.Camera.EProperty.Exposure, out fMin, out fMax);

			// Start the camera. Depending on the given trigger mode, the camera starts to capture images or waits for a trigger
			xCamera.Start(Rx.InteropNet.Runtime30.Camera.ETriggerMode.Camera_FreeRun);

			for (int iIdx = 0; iIdx < Rx.LFR.Net.Cuda.GetDeviceCount(); iIdx++)
			{
				// Assign the CUDA device and the calibration
				m_pxCudaCompute[iIdx] = new Rx.LFR.Net.CudaCompute();
				m_pxCudaCompute[iIdx].SetCudaDevice(Rx.LFR.Net.Cuda.GetDevice((int) iAssignedCudaDevice));
				m_pxCudaCompute[iIdx].ApplyCalibration(xDefaultCalibration, true);
				m_pxCudaCompute[iIdx].GetParams().ImportFromFile(xDepthSettingsPath);

				m_xThreads[iIdx] = new System.Threading.Thread(ProcessImage);
				m_xThreads[iIdx].Start(iIdx);
			}

			// Start visualization thread
			m_xComputedBuffer = new Rx.LFR.Net.ImageQueue();
			m_xComputedBuffer.Initialize(uBufferSize, bOverwrite);
			System.Threading.Thread xVisioThread = new System.Threading.Thread(ShowImage);
			xVisioThread.Start();

			Console.WriteLine("--------------------------------------------------------------------------------------------------");
			Console.WriteLine("Camera {0} with Index {1} is assigned to cuda device {2} with index {3}.", sCameraName, 0, sCudaName, iAssignedCudaDevice);
			Console.WriteLine("--------------------------------------------------------------------------------------------------");

			if (iAssignedCudaDevice < iCudaDevices - 1)
			{
				iAssignedCudaDevice++;
			}

			/************************************************************************/
			/* Wait                                                                 */
			/************************************************************************/

			// Press any key to stop the capturing
			Console.WriteLine("Press any key to exit.");
			Console.ReadKey();

			/************************************************************************/
			/* Stop Threads                                                         */
			/************************************************************************/
			m_bStopThread = true;

			foreach (System.Threading.Thread xThread in m_xThreads)
			{
				xThread.Join();
			}

			xVisioThread.Join();

			/************************************************************************/
			/* Close Cameras                                                        */
			/************************************************************************/
			Console.WriteLine("Close Cameras");
			for (uint uCameraIndex = 0; uCameraIndex < m_xCamServer.GetCameraCount(); uCameraIndex++)
			{
				// Stop the capture of the camera
				m_xCamServer.GetCamera(uCameraIndex).Stop();
				// Close the cameras and release the communication and its required memory
				m_xCamServer.GetCamera(uCameraIndex).Close();
			}

			// Release the camera server to free all found cameras. All cameras are invalid after this call
			m_xCamServer.Release();

			return 0;
		}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///     A program.
	/// </summary>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static class Program
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     The main entry point for the application.
		/// </summary>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static void Main()
		{
			new Example().Run();
		}
	}
}
