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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.seqDataGridView = new System.Windows.Forms.DataGridView();
            this.removeButton = new System.Windows.Forms.Button();
            this.colorPictureBox = new System.Windows.Forms.PictureBox();
            this.setColorButton = new System.Windows.Forms.Button();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.setAdvancedButton = new System.Windows.Forms.Button();
            this.basePictureBox = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.seqDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorPictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.basePictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // seqDataGridView
            // 
            this.seqDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.seqDataGridView.ColumnHeadersVisible = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.Color.White;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.seqDataGridView.DefaultCellStyle = dataGridViewCellStyle1;
            this.seqDataGridView.Location = new System.Drawing.Point(1, 2);
            this.seqDataGridView.Name = "seqDataGridView";
            this.seqDataGridView.ReadOnly = true;
            this.seqDataGridView.Size = new System.Drawing.Size(797, 114);
            this.seqDataGridView.TabIndex = 0;
            this.seqDataGridView.SelectionChanged += new System.EventHandler(this.seqDataGridView_SelectionChanged);
            this.seqDataGridView.DragDrop += new System.Windows.Forms.DragEventHandler(this.seqDataGridView_DragDrop);
            this.seqDataGridView.DragEnter += new System.Windows.Forms.DragEventHandler(this.seqDataGridView_DragEnter);
            // 
            // removeButton
            // 
            this.removeButton.Location = new System.Drawing.Point(260, 122);
            this.removeButton.Name = "removeButton";
            this.removeButton.Size = new System.Drawing.Size(75, 70);
            this.removeButton.TabIndex = 1;
            this.removeButton.Text = "Remove";
            this.removeButton.UseVisualStyleBackColor = true;
            this.removeButton.Click += new System.EventHandler(this.removeButton_Click);
            // 
            // colorPictureBox
            // 
            this.colorPictureBox.BackColor = System.Drawing.Color.White;
            this.colorPictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.colorPictureBox.Location = new System.Drawing.Point(12, 123);
            this.colorPictureBox.Name = "colorPictureBox";
            this.colorPictureBox.Size = new System.Drawing.Size(100, 97);
            this.colorPictureBox.TabIndex = 2;
            this.colorPictureBox.TabStop = false;
            this.colorPictureBox.DoubleClick += new System.EventHandler(this.colorPictureBox_DoubleClick);
            this.colorPictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.colorPictureBox_MouseDown);
            // 
            // setColorButton
            // 
            this.setColorButton.Location = new System.Drawing.Point(12, 226);
            this.setColorButton.Name = "setColorButton";
            this.setColorButton.Size = new System.Drawing.Size(49, 42);
            this.setColorButton.TabIndex = 3;
            this.setColorButton.Text = "Set Color";
            this.setColorButton.UseVisualStyleBackColor = true;
            this.setColorButton.Click += new System.EventHandler(this.setColorButton_Click);
            // 
            // setAdvancedButton
            // 
            this.setAdvancedButton.Location = new System.Drawing.Point(63, 226);
            this.setAdvancedButton.Name = "setAdvancedButton";
            this.setAdvancedButton.Size = new System.Drawing.Size(49, 42);
            this.setAdvancedButton.TabIndex = 4;
            this.setAdvancedButton.Text = "Set Adv";
            this.setAdvancedButton.UseVisualStyleBackColor = true;
            this.setAdvancedButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // basePictureBox
            // 
            this.basePictureBox.BackColor = System.Drawing.Color.White;
            this.basePictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.basePictureBox.Location = new System.Drawing.Point(130, 123);
            this.basePictureBox.Name = "basePictureBox";
            this.basePictureBox.Size = new System.Drawing.Size(40, 38);
            this.basePictureBox.TabIndex = 5;
            this.basePictureBox.TabStop = false;
            this.basePictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.basePictureBox_MouseDown);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 341);
            this.Controls.Add(this.basePictureBox);
            this.Controls.Add(this.setAdvancedButton);
            this.Controls.Add(this.setColorButton);
            this.Controls.Add(this.colorPictureBox);
            this.Controls.Add(this.removeButton);
            this.Controls.Add(this.seqDataGridView);
            this.Name = "Form1";
            this.Text = "Color Bar";
            ((System.ComponentModel.ISupportInitialize)(this.seqDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorPictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.basePictureBox)).EndInit();
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
    }
}

