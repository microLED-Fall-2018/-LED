namespace WindowsFormsApp1
{
    partial class Form1
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.portsBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.connectButton = new System.Windows.Forms.Button();
            this.rCheckBox = new System.Windows.Forms.CheckBox();
            this.gCheckBox = new System.Windows.Forms.CheckBox();
            this.bCheckBox = new System.Windows.Forms.CheckBox();
            this.rTrackBar = new System.Windows.Forms.TrackBar();
            this.gTrackBar = new System.Windows.Forms.TrackBar();
            this.bTrackBar = new System.Windows.Forms.TrackBar();
            this.rStrengthLabel = new System.Windows.Forms.Label();
            this.gStrengthLabel = new System.Windows.Forms.Label();
            this.bStrengthLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.rTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bTrackBar)).BeginInit();
            this.SuspendLayout();
            // 
            // portsBox
            // 
            this.portsBox.FormattingEnabled = true;
            this.portsBox.Location = new System.Drawing.Point(56, 13);
            this.portsBox.Name = "portsBox";
            this.portsBox.Size = new System.Drawing.Size(121, 21);
            this.portsBox.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
            this.label1.Location = new System.Drawing.Point(12, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Port:";
            // 
            // connectButton
            // 
            this.connectButton.Location = new System.Drawing.Point(183, 13);
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(75, 23);
            this.connectButton.TabIndex = 2;
            this.connectButton.Text = "Connnect";
            this.connectButton.UseVisualStyleBackColor = true;
            this.connectButton.Click += new System.EventHandler(this.connectButton_Click);
            // 
            // rCheckBox
            // 
            this.rCheckBox.AutoSize = true;
            this.rCheckBox.Location = new System.Drawing.Point(67, 210);
            this.rCheckBox.Name = "rCheckBox";
            this.rCheckBox.Size = new System.Drawing.Size(34, 17);
            this.rCheckBox.TabIndex = 3;
            this.rCheckBox.Text = "R";
            this.rCheckBox.UseVisualStyleBackColor = true;
            this.rCheckBox.CheckedChanged += new System.EventHandler(this.rCheckBox_CheckedChanged);
            // 
            // gCheckBox
            // 
            this.gCheckBox.AutoSize = true;
            this.gCheckBox.Location = new System.Drawing.Point(125, 210);
            this.gCheckBox.Name = "gCheckBox";
            this.gCheckBox.Size = new System.Drawing.Size(34, 17);
            this.gCheckBox.TabIndex = 4;
            this.gCheckBox.Text = "G";
            this.gCheckBox.UseVisualStyleBackColor = true;
            this.gCheckBox.CheckedChanged += new System.EventHandler(this.gCheckBox_CheckedChanged);
            // 
            // bCheckBox
            // 
            this.bCheckBox.AutoSize = true;
            this.bCheckBox.Location = new System.Drawing.Point(174, 210);
            this.bCheckBox.Name = "bCheckBox";
            this.bCheckBox.Size = new System.Drawing.Size(33, 17);
            this.bCheckBox.TabIndex = 5;
            this.bCheckBox.Text = "B";
            this.bCheckBox.UseVisualStyleBackColor = true;
            this.bCheckBox.CheckedChanged += new System.EventHandler(this.bCheckBox_CheckedChanged);
            // 
            // rTrackBar
            // 
            this.rTrackBar.Location = new System.Drawing.Point(67, 50);
            this.rTrackBar.Name = "rTrackBar";
            this.rTrackBar.Size = new System.Drawing.Size(104, 45);
            this.rTrackBar.TabIndex = 6;
            this.rTrackBar.Scroll += new System.EventHandler(this.rTrackBar_Scroll);
            // 
            // gTrackBar
            // 
            this.gTrackBar.Location = new System.Drawing.Point(67, 91);
            this.gTrackBar.Name = "gTrackBar";
            this.gTrackBar.Size = new System.Drawing.Size(104, 45);
            this.gTrackBar.TabIndex = 7;
            this.gTrackBar.Scroll += new System.EventHandler(this.gTrackBar_Scroll);
            // 
            // bTrackBar
            // 
            this.bTrackBar.Location = new System.Drawing.Point(67, 133);
            this.bTrackBar.Name = "bTrackBar";
            this.bTrackBar.Size = new System.Drawing.Size(104, 45);
            this.bTrackBar.TabIndex = 8;
            this.bTrackBar.Scroll += new System.EventHandler(this.bTrackBar_Scroll);
            // 
            // rStrengthLabel
            // 
            this.rStrengthLabel.AutoSize = true;
            this.rStrengthLabel.Location = new System.Drawing.Point(177, 60);
            this.rStrengthLabel.Name = "rStrengthLabel";
            this.rStrengthLabel.Size = new System.Drawing.Size(13, 13);
            this.rStrengthLabel.TabIndex = 9;
            this.rStrengthLabel.Text = "0";
            // 
            // gStrengthLabel
            // 
            this.gStrengthLabel.AutoSize = true;
            this.gStrengthLabel.Location = new System.Drawing.Point(177, 100);
            this.gStrengthLabel.Name = "gStrengthLabel";
            this.gStrengthLabel.Size = new System.Drawing.Size(13, 13);
            this.gStrengthLabel.TabIndex = 10;
            this.gStrengthLabel.Text = "0";
            // 
            // bStrengthLabel
            // 
            this.bStrengthLabel.AutoSize = true;
            this.bStrengthLabel.Location = new System.Drawing.Point(177, 144);
            this.bStrengthLabel.Name = "bStrengthLabel";
            this.bStrengthLabel.Size = new System.Drawing.Size(13, 13);
            this.bStrengthLabel.TabIndex = 11;
            this.bStrengthLabel.Text = "0";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.bStrengthLabel);
            this.Controls.Add(this.gStrengthLabel);
            this.Controls.Add(this.rStrengthLabel);
            this.Controls.Add(this.bTrackBar);
            this.Controls.Add(this.gTrackBar);
            this.Controls.Add(this.rTrackBar);
            this.Controls.Add(this.bCheckBox);
            this.Controls.Add(this.gCheckBox);
            this.Controls.Add(this.rCheckBox);
            this.Controls.Add(this.connectButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.portsBox);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.rTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bTrackBar)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox portsBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button connectButton;
        private System.Windows.Forms.CheckBox rCheckBox;
        private System.Windows.Forms.CheckBox gCheckBox;
        private System.Windows.Forms.CheckBox bCheckBox;
        private System.Windows.Forms.TrackBar rTrackBar;
        private System.Windows.Forms.TrackBar gTrackBar;
        private System.Windows.Forms.TrackBar bTrackBar;
        private System.Windows.Forms.Label rStrengthLabel;
        private System.Windows.Forms.Label gStrengthLabel;
        private System.Windows.Forms.Label bStrengthLabel;
    }
}

