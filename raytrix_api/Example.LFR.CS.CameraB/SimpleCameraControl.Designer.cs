namespace Example.LFR.CS
{
    partial class SimpleCameraControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.startButton = new System.Windows.Forms.Button();
            this.stopButton = new System.Windows.Forms.Button();
            this.numUpDownFPS = new System.Windows.Forms.NumericUpDown();
            this.numUpDownExposure = new System.Windows.Forms.NumericUpDown();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.labelCameraName = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownFPS)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownExposure)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // startButton
            // 
            this.startButton.Location = new System.Drawing.Point(139, 3);
            this.startButton.Name = "startButton";
            this.startButton.Size = new System.Drawing.Size(75, 23);
            this.startButton.TabIndex = 0;
            this.startButton.Text = "Start";
            this.startButton.UseVisualStyleBackColor = true;
            this.startButton.Click += new System.EventHandler(this.startButton_Click);
            // 
            // stopButton
            // 
            this.stopButton.Location = new System.Drawing.Point(220, 3);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(75, 23);
            this.stopButton.TabIndex = 1;
            this.stopButton.Text = "Stop";
            this.stopButton.UseVisualStyleBackColor = true;
            this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
            // 
            // numUpDownFPS
            // 
            this.numUpDownFPS.Location = new System.Drawing.Point(301, 3);
            this.numUpDownFPS.Name = "numUpDownFPS";
            this.numUpDownFPS.Size = new System.Drawing.Size(120, 20);
            this.numUpDownFPS.TabIndex = 2;
            this.numUpDownFPS.ValueChanged += new System.EventHandler(this.numUpDownFPS_ValueChanged);
            // 
            // numUpDownExposure
            // 
            this.numUpDownExposure.Location = new System.Drawing.Point(427, 3);
            this.numUpDownExposure.Name = "numUpDownExposure";
            this.numUpDownExposure.Size = new System.Drawing.Size(120, 20);
            this.numUpDownExposure.TabIndex = 3;
            this.numUpDownExposure.ValueChanged += new System.EventHandler(this.numUpDownExposure_ValueChanged);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.ColumnCount = 6;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.startButton, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.numUpDownExposure, 4, 0);
            this.tableLayoutPanel1.Controls.Add(this.stopButton, 2, 0);
            this.tableLayoutPanel1.Controls.Add(this.numUpDownFPS, 3, 0);
            this.tableLayoutPanel1.Controls.Add(this.labelCameraName, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(907, 158);
            this.tableLayoutPanel1.TabIndex = 4;
            // 
            // labelCameraName
            // 
            this.labelCameraName.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelCameraName.AutoSize = true;
            this.labelCameraName.Location = new System.Drawing.Point(3, 8);
            this.labelCameraName.MinimumSize = new System.Drawing.Size(130, 0);
            this.labelCameraName.Name = "labelCameraName";
            this.labelCameraName.Size = new System.Drawing.Size(130, 13);
            this.labelCameraName.TabIndex = 4;
            this.labelCameraName.Text = "?";
            // 
            // SimpleCameraControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "SimpleCameraControl";
            this.Size = new System.Drawing.Size(907, 158);
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownFPS)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownExposure)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button startButton;
        private System.Windows.Forms.Button stopButton;
        private System.Windows.Forms.NumericUpDown numUpDownFPS;
        private System.Windows.Forms.NumericUpDown numUpDownExposure;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label labelCameraName;
    }
}
