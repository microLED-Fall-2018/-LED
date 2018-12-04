namespace SeniorProjectMVC
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
            this.addPatternButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.savePatternButton = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.selectColorButton = new System.Windows.Forms.Button();
            this.selectedColorBox = new System.Windows.Forms.PictureBox();
            this.deletePatternButton = new System.Windows.Forms.Button();
            this.colorListView = new System.Windows.Forms.ListView();
            this.colorsColumn = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.label4 = new System.Windows.Forms.Label();
            this.patternNameTextBox = new System.Windows.Forms.TextBox();
            this.durationTrackBar = new System.Windows.Forms.TrackBar();
            this.label5 = new System.Windows.Forms.Label();
            this.durationLabel = new System.Windows.Forms.Label();
            this.addColor = new System.Windows.Forms.Button();
            this.removeColor = new System.Windows.Forms.Button();
            this.removePatternButton = new System.Windows.Forms.Button();
            this.patternsListView = new System.Windows.Forms.ListView();
            this.Patterns = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.setListView = new System.Windows.Forms.ListView();
            this.SetPatterns = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.exportButton = new System.Windows.Forms.Button();
            this.loadPatternButton = new System.Windows.Forms.Button();
            this.connectButton = new System.Windows.Forms.Button();
            this.portComboBox = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.selectedColorBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.durationTrackBar)).BeginInit();
            this.SuspendLayout();
            // 
            // addPatternButton
            // 
            this.addPatternButton.Location = new System.Drawing.Point(150, 167);
            this.addPatternButton.Name = "addPatternButton";
            this.addPatternButton.Size = new System.Drawing.Size(52, 23);
            this.addPatternButton.TabIndex = 2;
            this.addPatternButton.Text = "<--";
            this.addPatternButton.UseVisualStyleBackColor = true;
            this.addPatternButton.Click += new System.EventHandler(this.addPatternButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(79, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Patterns in Set:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(208, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Patterns:";
            // 
            // savePatternButton
            // 
            this.savePatternButton.Location = new System.Drawing.Point(341, 167);
            this.savePatternButton.Name = "savePatternButton";
            this.savePatternButton.Size = new System.Drawing.Size(52, 24);
            this.savePatternButton.TabIndex = 23;
            this.savePatternButton.Text = "<--";
            this.savePatternButton.Click += new System.EventHandler(this.savePatternButton_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(396, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(87, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Colors in Pattern:";
            // 
            // selectColorButton
            // 
            this.selectColorButton.Location = new System.Drawing.Point(645, 84);
            this.selectColorButton.Name = "selectColorButton";
            this.selectColorButton.Size = new System.Drawing.Size(75, 23);
            this.selectColorButton.TabIndex = 9;
            this.selectColorButton.Text = "Select Color";
            this.selectColorButton.UseVisualStyleBackColor = true;
            this.selectColorButton.Click += new System.EventHandler(this.selectColorButton_Click);
            // 
            // selectedColorBox
            // 
            this.selectedColorBox.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.selectedColorBox.Location = new System.Drawing.Point(535, 69);
            this.selectedColorBox.Name = "selectedColorBox";
            this.selectedColorBox.Size = new System.Drawing.Size(90, 85);
            this.selectedColorBox.TabIndex = 10;
            this.selectedColorBox.TabStop = false;
            // 
            // deletePatternButton
            // 
            this.deletePatternButton.BackColor = System.Drawing.SystemColors.Control;
            this.deletePatternButton.Location = new System.Drawing.Point(246, 403);
            this.deletePatternButton.Name = "deletePatternButton";
            this.deletePatternButton.Size = new System.Drawing.Size(52, 23);
            this.deletePatternButton.TabIndex = 20;
            this.deletePatternButton.Text = "X";
            this.deletePatternButton.UseVisualStyleBackColor = false;
            this.deletePatternButton.Click += new System.EventHandler(this.deletePatternButton_Click);
            // 
            // colorListView
            // 
            this.colorListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.colorsColumn});
            this.colorListView.FullRowSelect = true;
            this.colorListView.GridLines = true;
            this.colorListView.Location = new System.Drawing.Point(399, 29);
            this.colorListView.Name = "colorListView";
            this.colorListView.Size = new System.Drawing.Size(121, 368);
            this.colorListView.TabIndex = 12;
            this.colorListView.UseCompatibleStateImageBehavior = false;
            this.colorListView.View = System.Windows.Forms.View.Details;
            // 
            // colorsColumn
            // 
            this.colorsColumn.Text = "Colors";
            this.colorsColumn.Width = 116;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(532, 29);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(75, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Pattern Name:";
            // 
            // patternNameTextBox
            // 
            this.patternNameTextBox.Location = new System.Drawing.Point(613, 26);
            this.patternNameTextBox.Name = "patternNameTextBox";
            this.patternNameTextBox.Size = new System.Drawing.Size(107, 20);
            this.patternNameTextBox.TabIndex = 14;
            // 
            // durationTrackBar
            // 
            this.durationTrackBar.Location = new System.Drawing.Point(582, 188);
            this.durationTrackBar.Maximum = 100;
            this.durationTrackBar.Name = "durationTrackBar";
            this.durationTrackBar.Size = new System.Drawing.Size(132, 45);
            this.durationTrackBar.TabIndex = 15;
            this.durationTrackBar.TickStyle = System.Windows.Forms.TickStyle.None;
            this.durationTrackBar.Value = 10;
            this.durationTrackBar.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(532, 172);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(96, 13);
            this.label5.TabIndex = 16;
            this.label5.Text = "Color Duration (ms)";
            // 
            // durationLabel
            // 
            this.durationLabel.AutoSize = true;
            this.durationLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.durationLabel.Location = new System.Drawing.Point(529, 189);
            this.durationLabel.MinimumSize = new System.Drawing.Size(50, 25);
            this.durationLabel.Name = "durationLabel";
            this.durationLabel.Size = new System.Drawing.Size(50, 25);
            this.durationLabel.TabIndex = 17;
            this.durationLabel.Text = "50";
            this.durationLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // addColor
            // 
            this.addColor.Location = new System.Drawing.Point(399, 404);
            this.addColor.Name = "addColor";
            this.addColor.Size = new System.Drawing.Size(29, 23);
            this.addColor.TabIndex = 18;
            this.addColor.Text = "+";
            this.addColor.UseVisualStyleBackColor = true;
            this.addColor.Click += new System.EventHandler(this.addColor_Click);
            // 
            // removeColor
            // 
            this.removeColor.Location = new System.Drawing.Point(491, 404);
            this.removeColor.Name = "removeColor";
            this.removeColor.Size = new System.Drawing.Size(29, 23);
            this.removeColor.TabIndex = 19;
            this.removeColor.Text = "-";
            this.removeColor.UseVisualStyleBackColor = true;
            this.removeColor.Click += new System.EventHandler(this.removeColor_Click);
            // 
            // removePatternButton
            // 
            this.removePatternButton.Location = new System.Drawing.Point(150, 210);
            this.removePatternButton.Name = "removePatternButton";
            this.removePatternButton.Size = new System.Drawing.Size(52, 23);
            this.removePatternButton.TabIndex = 24;
            this.removePatternButton.Text = "-->";
            this.removePatternButton.UseVisualStyleBackColor = true;
            this.removePatternButton.Click += new System.EventHandler(this.removePatternButton_Click);
            // 
            // patternsListView
            // 
            this.patternsListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.Patterns});
            this.patternsListView.FullRowSelect = true;
            this.patternsListView.GridLines = true;
            this.patternsListView.Location = new System.Drawing.Point(211, 29);
            this.patternsListView.Name = "patternsListView";
            this.patternsListView.Size = new System.Drawing.Size(121, 368);
            this.patternsListView.TabIndex = 25;
            this.patternsListView.UseCompatibleStateImageBehavior = false;
            this.patternsListView.View = System.Windows.Forms.View.Details;
            // 
            // Patterns
            // 
            this.Patterns.Text = "Patterns";
            this.Patterns.Width = 115;
            // 
            // setListView
            // 
            this.setListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.SetPatterns});
            this.setListView.FullRowSelect = true;
            this.setListView.GridLines = true;
            this.setListView.Location = new System.Drawing.Point(23, 29);
            this.setListView.Name = "setListView";
            this.setListView.Size = new System.Drawing.Size(121, 368);
            this.setListView.TabIndex = 26;
            this.setListView.UseCompatibleStateImageBehavior = false;
            this.setListView.View = System.Windows.Forms.View.Details;
            // 
            // SetPatterns
            // 
            this.SetPatterns.Text = "Set Patterns";
            this.SetPatterns.Width = 115;
            // 
            // exportButton
            // 
            this.exportButton.Location = new System.Drawing.Point(41, 403);
            this.exportButton.Name = "exportButton";
            this.exportButton.Size = new System.Drawing.Size(75, 23);
            this.exportButton.TabIndex = 27;
            this.exportButton.Text = "Export Set";
            this.exportButton.UseVisualStyleBackColor = true;
            this.exportButton.Click += new System.EventHandler(this.exportButton_Click);
            // 
            // loadPatternButton
            // 
            this.loadPatternButton.Location = new System.Drawing.Point(341, 210);
            this.loadPatternButton.Name = "loadPatternButton";
            this.loadPatternButton.Size = new System.Drawing.Size(52, 23);
            this.loadPatternButton.TabIndex = 28;
            this.loadPatternButton.Text = "-->";
            this.loadPatternButton.UseVisualStyleBackColor = true;
            this.loadPatternButton.Click += new System.EventHandler(this.loadPatternButton_Click);
            // 
            // connectButton
            // 
            this.connectButton.Location = new System.Drawing.Point(639, 267);
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(75, 23);
            this.connectButton.TabIndex = 29;
            this.connectButton.Text = "Connect";
            this.connectButton.UseVisualStyleBackColor = true;
            this.connectButton.Click += new System.EventHandler(this.connectButton_Click);
            // 
            // portComboBox
            // 
            this.portComboBox.FormattingEnabled = true;
            this.portComboBox.Location = new System.Drawing.Point(535, 267);
            this.portComboBox.Name = "portComboBox";
            this.portComboBox.Size = new System.Drawing.Size(98, 21);
            this.portComboBox.TabIndex = 30;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(726, 450);
            this.Controls.Add(this.portComboBox);
            this.Controls.Add(this.connectButton);
            this.Controls.Add(this.loadPatternButton);
            this.Controls.Add(this.exportButton);
            this.Controls.Add(this.setListView);
            this.Controls.Add(this.patternsListView);
            this.Controls.Add(this.removePatternButton);
            this.Controls.Add(this.removeColor);
            this.Controls.Add(this.addColor);
            this.Controls.Add(this.durationLabel);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.durationTrackBar);
            this.Controls.Add(this.patternNameTextBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.colorListView);
            this.Controls.Add(this.deletePatternButton);
            this.Controls.Add(this.selectedColorBox);
            this.Controls.Add(this.selectColorButton);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.savePatternButton);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.addPatternButton);
            this.Name = "Form1";
            this.Text = "a";
            ((System.ComponentModel.ISupportInitialize)(this.selectedColorBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.durationTrackBar)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button addPatternButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button savePatternButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.Button selectColorButton;
        private System.Windows.Forms.PictureBox selectedColorBox;
        private System.Windows.Forms.Button deletePatternButton;
        private System.Windows.Forms.ListView colorListView;
        private System.Windows.Forms.ColumnHeader colorsColumn;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox patternNameTextBox;
        private System.Windows.Forms.TrackBar durationTrackBar;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label durationLabel;
        private System.Windows.Forms.Button addColor;
        private System.Windows.Forms.Button removeColor;
        private System.Windows.Forms.Button removePatternButton;
        private System.Windows.Forms.ListView patternsListView;
        private System.Windows.Forms.ColumnHeader Patterns;
        private System.Windows.Forms.ListView setListView;
        private System.Windows.Forms.ColumnHeader SetPatterns;
        private System.Windows.Forms.Button exportButton;
        private System.Windows.Forms.Button loadPatternButton;
        private System.Windows.Forms.Button connectButton;
        private System.Windows.Forms.ComboBox portComboBox;
    }
}

