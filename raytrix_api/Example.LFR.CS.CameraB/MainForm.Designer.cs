namespace Example.LFR.CS.CameraB
{
	partial class FormMain
	{
		private System.ComponentModel.IContainer components = null;

		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Vom Windows Form-Designer generierter Code

		private
		void InitializeComponent()
        {
            this.tableLayoutPanelCameraControls = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.label1 = new System.Windows.Forms.Label();
            this.numUpDownBufferSize = new System.Windows.Forms.NumericUpDown();
            this.checkBoxOverride = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteLog = new System.Windows.Forms.CheckBox();
            this.buttonStartExample = new System.Windows.Forms.Button();
            this.buttonStopExample = new System.Windows.Forms.Button();
            this.tableLayoutPanelCameraControls.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownBufferSize)).BeginInit();
            this.SuspendLayout();
            //
            // tableLayoutPanelCameraControls
            //
            this.tableLayoutPanelCameraControls.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanelCameraControls.AutoSize = true;
            this.tableLayoutPanelCameraControls.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanelCameraControls.ColumnCount = 1;
            this.tableLayoutPanelCameraControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanelCameraControls.Controls.Add(this.tableLayoutPanel1, 0, 0);
            this.tableLayoutPanelCameraControls.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanelCameraControls.Name = "tableLayoutPanelCameraControls";
            this.tableLayoutPanelCameraControls.RowCount = 2;
            this.tableLayoutPanelCameraControls.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanelCameraControls.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanelCameraControls.Size = new System.Drawing.Size(574, 169);
            this.tableLayoutPanelCameraControls.TabIndex = 0;
            //
            // tableLayoutPanel1
            //
            this.tableLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.numUpDownBufferSize, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.checkBoxOverride, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.checkBoxWriteLog, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.buttonStartExample, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.buttonStopExample, 1, 3);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 5;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(568, 113);
            this.tableLayoutPanel1.TabIndex = 1;
            //
            // label1
            //
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(87, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Imagebuffer size:";
            //
            // numUpDownBufferSize
            //
            this.numUpDownBufferSize.Location = new System.Drawing.Point(131, 3);
            this.numUpDownBufferSize.Name = "numUpDownBufferSize";
            this.numUpDownBufferSize.Size = new System.Drawing.Size(120, 20);
            this.numUpDownBufferSize.TabIndex = 1;
            this.numUpDownBufferSize.Value = new decimal(new int[] {
            3,
            0,
            0,
            0});
            //
            // checkBoxOverride
            //
            this.checkBoxOverride.AutoSize = true;
            this.tableLayoutPanel1.SetColumnSpan(this.checkBoxOverride, 2);
            this.checkBoxOverride.Location = new System.Drawing.Point(3, 29);
            this.checkBoxOverride.Name = "checkBoxOverride";
            this.checkBoxOverride.Size = new System.Drawing.Size(123, 17);
            this.checkBoxOverride.TabIndex = 2;
            this.checkBoxOverride.Text = "Imagebuffer override";
            this.checkBoxOverride.UseVisualStyleBackColor = true;
            //
            // checkBoxWriteLog
            //
            this.checkBoxWriteLog.AutoSize = true;
            this.checkBoxWriteLog.Location = new System.Drawing.Point(3, 52);
            this.checkBoxWriteLog.Name = "checkBoxWriteLog";
            this.checkBoxWriteLog.Size = new System.Drawing.Size(122, 17);
            this.checkBoxWriteLog.TabIndex = 3;
            this.checkBoxWriteLog.Text = "Write camera log file";
            this.checkBoxWriteLog.UseVisualStyleBackColor = true;
            //
            // buttonStartExample
            //
            this.buttonStartExample.Location = new System.Drawing.Point(3, 75);
            this.buttonStartExample.Name = "buttonStartExample";
            this.buttonStartExample.Size = new System.Drawing.Size(107, 23);
            this.buttonStartExample.TabIndex = 4;
            this.buttonStartExample.Text = "Start Example";
            this.buttonStartExample.UseVisualStyleBackColor = true;
            this.buttonStartExample.Click += new System.EventHandler(this.buttonStartExample_Click);
            //
            // buttonStopExample
            //
            this.buttonStopExample.Enabled = false;
            this.buttonStopExample.Location = new System.Drawing.Point(131, 75);
            this.buttonStopExample.Name = "buttonStopExample";
            this.buttonStopExample.Size = new System.Drawing.Size(107, 23);
            this.buttonStopExample.TabIndex = 5;
            this.buttonStopExample.Text = "Stop Example";
            this.buttonStopExample.UseVisualStyleBackColor = true;
            this.buttonStopExample.Click += new System.EventHandler(this.buttonStopExample_Click);
            //
            // FormMain
            //
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(574, 373);
            this.Controls.Add(this.tableLayoutPanelCameraControls);
            this.Name = "FormMain";
            this.Text = "Raytrix C# MGPU Example";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            this.Shown += new System.EventHandler(this.FormMain_Shown);
            this.tableLayoutPanelCameraControls.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownBufferSize)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanelCameraControls;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.NumericUpDown numUpDownBufferSize;
        private System.Windows.Forms.CheckBox checkBoxOverride;
        private System.Windows.Forms.CheckBox checkBoxWriteLog;
        private System.Windows.Forms.Button buttonStartExample;
        private System.Windows.Forms.Button buttonStopExample;

    }
}
