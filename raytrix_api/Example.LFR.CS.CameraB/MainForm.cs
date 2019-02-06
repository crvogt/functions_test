/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2015 Raytrix GmbH. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: Example.LFR.CS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Example.LFR.CS.CameraB
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///     A form main.
	/// </summary>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public partial class FormMain : Form
	{
		/// <summary> The CUDA compute class. </summary>
		Rx.LFR.Net.CudaCompute[] m_pxCudaCompute;
		/// <summary> The visualization handles. </summary>
		int[] m_aiHandles;
		/// <summary> The camera server class that is able to find attached cameras. </summary>
		Rx.LFR.Net.CameraServer m_xCamServer;
		/// <summary> The camera buffers. </summary>
		Rx.LFR.Net.ImageQueue[] m_xCamBuffers;
		/// <summary> The threads. </summary>
		System.Threading.Thread[] m_xThreads;
		/// <summary> The stream writer. </summary>
		System.IO.StreamWriter[] m_swLog;
		/// <summary> The camera controls. </summary>
		SimpleCameraControl[] m_xCameraControls;
		/// <summary> true to stop thread. </summary>
		bool m_bStopThread = false;
		/// <summary> true if inistialized. </summary>
		bool m_bInistialized = false;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Constructor.
		/// </summary>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public FormMain()
		{
			try
			{
				InitializeComponent();
			}
			catch (Rx.Net.RxException xEx)
			{
				MessageBox.Show(xEx.ToString());
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Event handler. Called by FormMain for shown events.
		/// </summary>
		///
		/// <param name="sender">   Source of the event. </param>
		/// <param name="e">        Event information. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		private void FormMain_Shown(object sender, EventArgs e)
		{
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Form main change exposure.
		/// </summary>
		///
		/// <param name="uValue"> The value. </param>
		/// <param name="dValue"> The value. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void FormMain_ChangeExposure(uint uValue, double dValue)
		{
			// Get the camera from our camera server
			Rx.LFR.Net.Camera xCamera = m_xCamServer.GetCamera(uValue);
			xCamera.SetProperty(Rx.InteropNet.Runtime30.Camera.EProperty.Exposure, (float) dValue);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Form main change FPS.
		/// </summary>
		///
		/// <param name="uValue"> The value. </param>
		/// <param name="dValue"> The value. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void FormMain_ChangeFPS(uint uValue, double dValue)
		{
			// Get the camera from our camera server
			Rx.LFR.Net.Camera xCamera = m_xCamServer.GetCamera(uValue);
			xCamera.SetProperty(Rx.InteropNet.Runtime30.Camera.EProperty.Framerate, (float) dValue);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Form main stop camera.
		/// </summary>
		///
		/// <param name="uValue"> The value. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void FormMain_StopCamera(uint uValue)
		{
			// Get the camera from our camera server
			Rx.LFR.Net.Camera xCamera = m_xCamServer.GetCamera(uValue);
			xCamera.Stop();
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Form main start camera.
		/// </summary>
		///
		/// <param name="uValue"> The value. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void FormMain_StartCamera(uint uValue)
		{
			// Get the camera from our camera server
			Rx.LFR.Net.Camera xCamera = m_xCamServer.GetCamera(uValue);
			xCamera.Start();
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Uninitialize and free everything when the main form is closed.
		/// </summary>
		///
		/// <param name="sender">   Source of the event. </param>
		/// <param name="e">        Form closing event information. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
		{
			try
			{
				if (m_bInistialized)
				{
					/************************************************************************/
					/* Stop Threads                                                         */
					/************************************************************************/
					m_bStopThread = true;

					foreach (System.Threading.Thread xThread in m_xThreads)
					{
						xThread.Join();
					}

					/************************************************************************/
					/* Close Cameras                                                        */
					/************************************************************************/
					Print.Header("Close Cameras");
					for (uint uCameraIndex = 0; uCameraIndex < m_xCamServer.GetCameraCount(); uCameraIndex++)
					{
						// Stop the capture of the camera
						m_xCamServer.GetCamera(uCameraIndex).Stop();
						// Close the cameras and release the communication and its required memory
						m_xCamServer.GetCamera(uCameraIndex).Close();
					}

					// Release the camera server to free all found cameras. All cameras are invalid after this call
					m_xCamServer.Release();
				}
			}
			catch (Rx.Net.RxException xEx)
			{
				MessageBox.Show(xEx.ToString());
			}
		}

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
			if (!m_xCamBuffers[uCameraIndex].CopyIn(xConstImage))
			{
				// Buffer is full and overwrite is disabled
				// This is a lost frame
				return;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Write camera information.
		/// </summary>
		///
		/// <param name="uCameraIndex"> Zero-based index of the camera. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void CameraInfo(object uCameraIndex)
		{
			string sLogFile = "Camera_" + System.Convert.ToString(uCameraIndex) + ".txt";

			m_swLog[(uint) uCameraIndex] = System.IO.File.AppendText(sLogFile);

			// As long as this application is not stopped
			while (!m_bStopThread)
			{
				float fFps = 0.0f;
				m_xCamServer.GetCamera((uint) uCameraIndex).GetProperty(Rx.InteropNet.Runtime30.Camera.EProperty.Framerate, out fFps);

				float fActualFps = 0.0f;
				m_xCamServer.GetCamera((uint) uCameraIndex).GetProperty(Rx.InteropNet.Runtime30.Camera.EProperty.ActualFramerate, out fActualFps);

				m_swLog[(uint) uCameraIndex].Write("\r\nActual FPS : ");
				m_swLog[(uint) uCameraIndex].WriteLine("{0} {1}", DateTime.Now.ToLongTimeString(), DateTime.Now.ToLongDateString());
				m_swLog[(uint) uCameraIndex].WriteLine(":{0}", fFps);
				m_swLog[(uint) uCameraIndex].WriteLine(":{0}", fActualFps);
				m_swLog[(uint) uCameraIndex].WriteLine("-------------------------------");

				System.Threading.Thread.Sleep(1000);
			}

			m_swLog[(uint) uCameraIndex].Close();
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Process the image.
		/// </summary>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void ProcessImage(object uCameraIndex)
		{
			// As long as this application is not stopped
			while (!m_bStopThread)
			{
				try
				{
					// Wait for the image buffer to be not empty
					if (m_xCamBuffers[(uint) uCameraIndex].WaitForNotEmpty(1000))
					{
						// Get the first image in the Queue
						Rx.Net.Image xImage = new Rx.Net.Image();
						if (!m_xCamBuffers[(uint) uCameraIndex].MoveOut(xImage))
						{
							// Wait again! This functions says that it waits until a frame is available
							continue;
						}

						// Get the CUDA compute class for this camera
						Rx.LFR.Net.CudaCompute xCudaCompute = m_pxCudaCompute[(uint) uCameraIndex];

						// Upload the captured image as the new raw image of all further CUDA computations
						xCudaCompute.UploadRawImage(xImage);

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

						// Download images into the host memory
						Rx.Net.Image xImgDepthMap      = new Rx.Net.Image();
						Rx.Net.Image xImgDepthMapColor = new Rx.Net.Image();
						Rx.Net.Image xImgRefocus       = new Rx.Net.Image();
						xImages.Download(Rx.LFR.Net.EImage.DepthMap_View_Object_Pinhole, xImgDepthMap);
						xImages.Download(Rx.LFR.Net.EImage.DepthMapColored_View_Object_Pinhole, xImgDepthMapColor);
						xImages.Download(Rx.LFR.Net.EImage.RefocusBasic, xImgRefocus);

						// Do own host image processing
						// ...

						// Get CUDA image pointer
						//void* pvCudaPointer = xImages.GetImageDevicePointer(Rx.LFR.Net.EImage.DepthMap_View_Object_Pinhole);

						// Do own CUDA image processing
						// ...

						// Show the Image results
						CLUViz.Net.Tool.ViewSetImage(m_aiHandles[(uint) uCameraIndex], xImgDepthMapColor);

						xImgDepthMapColor.Dispose();
						xImage.Dispose();
						xImgDepthMap.Dispose();
						xImgRefocus.Dispose();
					}
					else
					{
						// If the queue is empty show a black image and wait again
						Rx.Net.ImageFormat xFormat = new Rx.Net.ImageFormat(100, 100, Rx.InteropNet.Runtime28.EPixelType.Lum, Rx.InteropNet.Runtime28.EDataType.UInt);
						Rx.Net.Image xImage        = new Rx.Net.Image(xFormat);
						xImage.SetZero();
						CLUViz.Net.Tool.ViewSetImage(m_aiHandles[0], xImage);
						xImage.Dispose();

						System.Console.WriteLine("Time out");
					}
				}
				catch (Rx.Net.RxException ex)
				{
					Print.Header("Exception");
					Console.WriteLine("\n\n\nOnImageCaptured Exception:\n\n\n{0}\n\n\n", ex.ToString(true));
					System.Environment.Exit(-1);
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Executes the status action.
		/// </summary>
		///
		/// <param name="eSource">  Source for the. </param>
		/// <param name="eMsg">     The message. </param>
		/// <param name="sSource">  Source for the. </param>
		/// <param name="sMessage"> The message. </param>
		/// <param name="iValue">   Zero-based index of the value. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void OnStatus(Rx.LFR.Net.EStatusMsgSrc eSource, Rx.LFR.Net.EStatusMsg eMsg, string sSource, string sMessage, int iValue)
		{
			// Print the status message
			Console.WriteLine("[{0}] {1, " + iValue * 4 + "}", sSource, sMessage);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Event handler. Called by buttonStartExample for click events.
		/// </summary>
		///
		/// <param name="sender"> Source of the event. </param>
		/// <param name="e">      Event information. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		private void buttonStartExample_Click(object sender, EventArgs e)
		{
			m_bInistialized = true;

			CLUViz.Net.Tool.Init();

			/************************************************************************/
			/* Authenticate LFR                                                     */
			/************************************************************************/
			Rx.LFR.Net.LightFieldRuntime.Authenticate();

			///  Initialize the calibration manager.
			Rx.LFR.Net.CalibrationManager.Initialize();

			// Enumerate all CUDA devices at the beginning
			Rx.LFR.Net.Cuda.EnumerateCudaDevices();

			uint uBufferSize = System.Convert.ToUInt32(numUpDownBufferSize.Value);
			bool bOverwrite  = checkBoxOverride.Checked;
			bool bWriteLog   = checkBoxWriteLog.Checked;

			numUpDownBufferSize.Enabled = false;
			checkBoxOverride.Enabled    = false;
			checkBoxWriteLog.Enabled    = false;
			buttonStartExample.Enabled  = false;
			buttonStopExample.Enabled   = true;

			/************************************************************************/
			/* CUDA                                                                 */
			/************************************************************************/
			int iCudaDevices = Rx.LFR.Net.Cuda.GetDeviceCount();

			Print.Header("CUDA Devices");
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
			Print.Header("Find Cameras");

			// Add a status message callback if you are interested in status messages sent by the camera server while finding cameras
			m_xCamServer                = new Rx.LFR.Net.CameraServer();
			m_xCamServer.StatusMessage += OnStatus;

			// Start to find cameras. This is an synchronous call and we wait here until the find process has been finished
			m_xCamServer.FindCameras();

			// Quit the application if there is no camera
			if (m_xCamServer.GetCameraCount() == 0)
			{
				Console.Write("No camera found\n");
				return;
			}

			m_pxCudaCompute   = new Rx.LFR.Net.CudaCompute[m_xCamServer.GetCameraCount()];
			m_aiHandles       = new int[m_xCamServer.GetCameraCount()];
			m_xThreads        = new System.Threading.Thread[m_xCamServer.GetCameraCount() * (bWriteLog ? 2 : 1)];
			m_xCamBuffers     = new Rx.LFR.Net.ImageQueue[m_xCamServer.GetCameraCount()];
			m_xCameraControls = new SimpleCameraControl[m_xCamServer.GetCameraCount()];

			if (bWriteLog)
			{
				m_swLog = new System.IO.StreamWriter[m_xCamServer.GetCameraCount()];
			}

			/************************************************************************/
			/* Start Cameras                                                        */
			/************************************************************************/
			Print.Header("Start Cameras");
			int iAssignedCudaDevice = 0;
			for (uint uCameraIndex = 0; uCameraIndex < m_xCamServer.GetCameraCount(); uCameraIndex++)
			{
				/************************************************************************/
				/* Initialize Buffer                                                    */
				/************************************************************************/

				// Create buffer within the given size and with the given overwrite flag
				m_xCamBuffers[uCameraIndex] = new Rx.LFR.Net.ImageQueue();
				m_xCamBuffers[uCameraIndex].Initialize(uBufferSize, bOverwrite);

				// Get the camera from our camera server
				Rx.LFR.Net.Camera xCamera = m_xCamServer.GetCamera(uCameraIndex);

				// Load the default calibration of the camera (and load the gray image too)
				Rx.LFR.Net.Calibration xDefaultCalibration = new Rx.LFR.Net.Calibration();
				Rx.LFR.Net.CalibrationManager.LoadDefaultCalibration(xDefaultCalibration, xCamera, true);
				Rx.LFR.Net.IParameters<Rx.LFR.Net.Params.ECalib> calibParams = xDefaultCalibration.GetParams();
				// Open the camera. This prepares the communication with the camera and checks the connection of GigE cameras
				// This does NOT start the camera stream
				xCamera.Open();

				// Add a image captured callback. This method gets called for every captured camera image and more details are given there
				xCamera.ImageCaptured += OnImageCaptured;

				// Assign the CUDA device and the calibration
				m_pxCudaCompute[uCameraIndex] = new Rx.LFR.Net.CudaCompute();
				m_pxCudaCompute[uCameraIndex].SetCudaDevice(Rx.LFR.Net.Cuda.GetDevice((int) iAssignedCudaDevice));
				m_pxCudaCompute[uCameraIndex].ApplyCalibration(xDefaultCalibration, true);

				string sName;
				(Rx.LFR.Net.Cuda.GetDevice((int) iAssignedCudaDevice)).GetParams().GetValue(Rx.LFR.Net.Params.ECudaDevice.Name, out sName);

				// Create the visualization
				// If there is one image buffer per camera set the view caption to the camera name;
				string sCameraName = Rx.LFR.Net.CalibrationManager.GetCameraName(xCamera);
				m_aiHandles[uCameraIndex] = CLUViz.Net.Tool.CreateViewImage((int) uCameraIndex * 1050, 0, 1000, 800, sCameraName);

				float fMin = 0.0f;
				float fMax = 0.0f;
				xCamera.GetPropertyRange(Rx.InteropNet.Runtime30.Camera.EProperty.Framerate, out fMin, out fMax);
				xCamera.SetProperty(Rx.InteropNet.Runtime30.Camera.EProperty.Framerate, fMax);
				System.Console.WriteLine("Setting Camera {0} to its max FPS: {1}", sCameraName, fMax);

				xCamera.GetPropertyRange(Rx.InteropNet.Runtime30.Camera.EProperty.Exposure, out fMin, out fMax);

				/************************************************************************/
				/* Initialize Control                                                   */
				/************************************************************************/
				m_xCameraControls[uCameraIndex]                 = new SimpleCameraControl(sCameraName, uCameraIndex, fMax, fMin);
				m_xCameraControls[uCameraIndex].StartCamera    += FormMain_StartCamera;
				m_xCameraControls[uCameraIndex].StopCamera     += FormMain_StopCamera;
				m_xCameraControls[uCameraIndex].ChangeFPS      += FormMain_ChangeFPS;
				m_xCameraControls[uCameraIndex].ChangeExposure += FormMain_ChangeExposure;
				tableLayoutPanelCameraControls.RowCount++;
				tableLayoutPanelCameraControls.RowStyles.Add(new RowStyle(SizeType.Absolute, 50F));
				tableLayoutPanelCameraControls.Controls.Add(m_xCameraControls[uCameraIndex], 0, tableLayoutPanelCameraControls.RowCount - 1);

				// Start the camera. Depending on the given trigger mode, the camera starts to capture images or waits for a trigger
				xCamera.Start(Rx.InteropNet.Runtime30.Camera.ETriggerMode.Camera_FreeRun);

				m_xThreads[uCameraIndex] = new System.Threading.Thread(ProcessImage);
				m_xThreads[uCameraIndex].Start(uCameraIndex);

				if (bWriteLog)
				{
					m_xThreads[m_xCamServer.GetCameraCount() + uCameraIndex] = new System.Threading.Thread(CameraInfo);
					m_xThreads[m_xCamServer.GetCameraCount() + uCameraIndex].Start(uCameraIndex);
				}

				Console.WriteLine("--------------------------------------------------------------------------------------------------");
				Console.WriteLine("Camera {0} with Index {1} is assigned to cuda device {2} with index {3}.", sCameraName, uCameraIndex, sName, iAssignedCudaDevice);
				Console.WriteLine("--------------------------------------------------------------------------------------------------");

				if (iAssignedCudaDevice < iCudaDevices - 1)
				{
					iAssignedCudaDevice++;
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Event handler. Called by buttonStopExample for click events.
		/// </summary>
		///
		/// <param name="sender"> Source of the event. </param>
		/// <param name="e">      Event information. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		private void buttonStopExample_Click(object sender, EventArgs e)
		{
			Close();
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///     the print class.
	/// </summary>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static class Print
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		///     Header.
		/// </summary>
		///
		/// <param name="sString"> The string. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public static void Header(string sString)
		{
			Console.Write("\n\n");
			Console.Write("====================================================================\n");
			Console.Write("===    {0}\n", sString);
			Console.Write("====================================================================\n\n");
		}
	}
}
