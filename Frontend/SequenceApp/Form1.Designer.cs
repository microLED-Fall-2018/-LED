namespace SequenceApp
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.seqDataGridView = new System.Windows.Forms.DataGridView();
            this.removeButton = new System.Windows.Forms.Button();
            this.colorPictureBox = new System.Windows.Forms.PictureBox();
            this.setColorButton = new System.Windows.Forms.Button();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.setAdvancedButton = new System.Windows.Forms.Button();
            this.basePictureBox = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.comComboBox = new System.Windows.Forms.ComboBox();
            this.connectButton = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.programCheckBox = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.numericUpDown2 = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.seqDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorPictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.basePictureBox)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).BeginInit();
            this.SuspendLayout();
            // 
            // seqDataGridView
            // 
            this.seqDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.seqDataGridView.ColumnHeadersVisible = false;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.Color.White;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.seqDataGridView.DefaultCellStyle = dataGridViewCellStyle2;
            this.seqDataGridView.Location = new System.Drawing.Point(1, 2);
            this.seqDataGridView.Name = "seqDataGridView";
            this.seqDataGridView.ReadOnly = true;
            this.seqDataGridView.Size = new System.Drawing.Size(315, 114);
            this.seqDataGridView.TabIndex = 0;
            this.seqDataGridView.SelectionChanged += new System.EventHandler(this.seqDataGridView_SelectionChanged);
            this.seqDataGridView.DragDrop += new System.Windows.Forms.DragEventHandler(this.seqDataGridView_DragDrop);
            this.seqDataGridView.DragEnter += new System.Windows.Forms.DragEventHandler(this.seqDataGridView_DragEnter);
            // 
            // removeButton
            // 
            this.removeButton.Location = new System.Drawing.Point(6, 178);
            this.removeButton.Name = "removeButton";
            this.removeButton.Size = new System.Drawing.Size(83, 33);
            this.removeButton.TabIndex = 1;
            this.removeButton.Text = "Remove";
            this.removeButton.UseVisualStyleBackColor = true;
            this.removeButton.Click += new System.EventHandler(this.removeButton_Click);
            // 
            // colorPictureBox
            // 
            this.colorPictureBox.BackColor = System.Drawing.Color.White;
            this.colorPictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.colorPictureBox.Location = new System.Drawing.Point(6, 16);
            this.colorPictureBox.Name = "colorPictureBox";
            this.colorPictureBox.Size = new System.Drawing.Size(82, 75);
            this.colorPictureBox.TabIndex = 2;
            this.colorPictureBox.TabStop = false;
            this.colorPictureBox.DoubleClick += new System.EventHandler(this.colorPictureBox_DoubleClick);
            this.colorPictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.colorPictureBox_MouseDown);
            // 
            // setColorButton
            // 
            this.setColorButton.Location = new System.Drawing.Point(6, 97);
            this.setColorButton.Name = "setColorButton";
            this.setColorButton.Size = new System.Drawing.Size(83, 36);
            this.setColorButton.TabIndex = 3;
            this.setColorButton.Text = "Set Color";
            this.setColorButton.UseVisualStyleBackColor = true;
            this.setColorButton.Click += new System.EventHandler(this.setColorButton_Click);
            // 
            // setAdvancedButton
            // 
            this.setAdvancedButton.Location = new System.Drawing.Point(6, 139);
            this.setAdvancedButton.Name = "setAdvancedButton";
            this.setAdvancedButton.Size = new System.Drawing.Size(83, 33);
            this.setAdvancedButton.TabIndex = 4;
            this.setAdvancedButton.Text = "Set Mode";
            this.setAdvancedButton.UseVisualStyleBackColor = true;
            this.setAdvancedButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // basePictureBox
            // 
            this.basePictureBox.BackColor = System.Drawing.Color.White;
            this.basePictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.basePictureBox.Location = new System.Drawing.Point(6, 16);
            this.basePictureBox.Name = "basePictureBox";
            this.basePictureBox.Size = new System.Drawing.Size(59, 54);
            this.basePictureBox.TabIndex = 5;
            this.basePictureBox.TabStop = false;
            this.basePictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.basePictureBox_MouseDown);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.numericUpDown1);
            this.groupBox1.Controls.Add(this.basePictureBox);
            this.groupBox1.Location = new System.Drawing.Point(115, 123);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(190, 79);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Single Slot";
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDown1.Location = new System.Drawing.Point(97, 39);
            this.numericUpDown1.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(76, 20);
            this.numericUpDown1.TabIndex = 6;
            this.numericUpDown1.Value = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDown1.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(116, 102);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(68, 22);
            this.button1.TabIndex = 2;
            this.button1.Text = "Export";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.removeButton);
            this.groupBox3.Controls.Add(this.colorPictureBox);
            this.groupBox3.Controls.Add(this.setColorButton);
            this.groupBox3.Controls.Add(this.setAdvancedButton);
            this.groupBox3.Location = new System.Drawing.Point(12, 123);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(97, 214);
            this.groupBox3.TabIndex = 8;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Beat Controls";
            // 
            // comComboBox
            // 
            this.comComboBox.FormattingEnabled = true;
            this.comComboBox.Location = new System.Drawing.Point(6, 77);
            this.comComboBox.Name = "comComboBox";
            this.comComboBox.Size = new System.Drawing.Size(178, 21);
            this.comComboBox.TabIndex = 10;
            this.comComboBox.DropDown += new System.EventHandler(this.comComboBox_DropDown);
            // 
            // connectButton
            // 
            this.connectButton.Location = new System.Drawing.Point(6, 102);
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(74, 22);
            this.connectButton.TabIndex = 11;
            this.connectButton.Text = "Connect";
            this.connectButton.UseVisualStyleBackColor = true;
            this.connectButton.Click += new System.EventHandler(this.connectButton_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.numericUpDown2);
            this.groupBox4.Controls.Add(this.programCheckBox);
            this.groupBox4.Controls.Add(this.label2);
            this.groupBox4.Controls.Add(this.label1);
            this.groupBox4.Controls.Add(this.comComboBox);
            this.groupBox4.Controls.Add(this.button1);
            this.groupBox4.Controls.Add(this.connectButton);
            this.groupBox4.Location = new System.Drawing.Point(115, 208);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(190, 129);
            this.groupBox4.TabIndex = 12;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Serial Communication";
            // 
            // programCheckBox
            // 
            this.programCheckBox.AutoSize = true;
            this.programCheckBox.Location = new System.Drawing.Point(14, 30);
            this.programCheckBox.Name = "programCheckBox";
            this.programCheckBox.Size = new System.Drawing.Size(65, 17);
            this.programCheckBox.TabIndex = 15;
            this.programCheckBox.Text = "Program";
            this.programCheckBox.UseVisualStyleBackColor = true;
            this.programCheckBox.CheckedChanged += new System.EventHandler(this.programCheckBox_CheckedChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(94, 31);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(28, 13);
            this.label2.TabIndex = 14;
            this.label2.Text = "Slot:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 61);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(72, 13);
            this.label1.TabIndex = 12;
            this.label1.Text = "COM Controls";
            // 
            // numericUpDown2
            // 
            this.numericUpDown2.Location = new System.Drawing.Point(129, 27);
            this.numericUpDown2.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDown2.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown2.Name = "numericUpDown2";
            this.numericUpDown2.Size = new System.Drawing.Size(55, 20);
            this.numericUpDown2.TabIndex = 16;
            this.numericUpDown2.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown2.ValueChanged += new System.EventHandler(this.numericUpDown2_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(97, 20);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(52, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Intentsity:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(318, 338);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.seqDataGridView);
            this.Name = "Form1";
            this.Text = "Color Bar";
            ((System.ComponentModel.ISupportInitialize)(this.seqDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorPictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.basePictureBox)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView seqDataGridView;
        private System.Windows.Forms.Button removeButton;
        private System.Windows.Forms.PictureBox colorPictureBox;
        private System.Windows.Forms.Button setColorButton;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.Button setAdvancedButton;
        private System.Windows.Forms.PictureBox basePictureBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox comComboBox;
        private System.Windows.Forms.Button connectButton;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.CheckBox programCheckBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numericUpDown2;
        private System.Windows.Forms.Label label3;
    }
}

