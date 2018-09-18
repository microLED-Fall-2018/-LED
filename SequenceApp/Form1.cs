using SequenceApp.View;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SequenceApp
{
    public partial class Form1 : Form, iForm1
    {
        public Form1()
        {
            InitializeComponent();

            // initialize rows/columns

            seqDataGridView.RowCount = 4;
            seqDataGridView.AllowDrop = true;
            var columns = new DataGridViewCustomColumn[50];
            for (int i = 0; i < 50; i++)
            {
                columns[i]= new DataGridViewCustomColumn();
                columns[i].Width = seqDataGridView.Rows[0].Height + 2;
            }

            //basePictureBox.Image = new Bitmap(@"D:\Desktop\Active HW\Senior Project\square_wave.png");

            seqDataGridView.Columns.AddRange(columns);
            seqDataGridView.Columns.RemoveAt(0);
            //seqDataGridView.ColumnCount = 50;
            for (int r = 0; r < seqDataGridView.RowCount; r++)
            {
                for (int c = 0; c < seqDataGridView.ColumnCount; c++)
                {
                    Bitmap image = new Bitmap(@"D:\Desktop\Active HW\Senior Project\square_wave.png");
                    image.SetResolution(10, 10);
                    seqDataGridView.Rows[r].Cells[c].Value = image;
                    seqDataGridView.Rows[r].Cells[c].Style.BackColor = Color.White;
                }
            }
            // initial formating
            seqDataGridView.RowHeadersWidth = seqDataGridView.RowHeadersWidth + 8;

            seqDataGridView.Rows[0].HeaderCell.Value = "R";
            seqDataGridView.Rows[1].HeaderCell.Value = "G";
            seqDataGridView.Rows[2].HeaderCell.Value = "B";
            seqDataGridView.Rows[3].HeaderCell.Value = "C";

            seqDataGridView.AllowUserToResizeColumns = false;
            seqDataGridView.AllowUserToResizeRows = false;
        }

        public event Action<Color, int> AddBeatClicked;
        public event Action<Color, int> AddColorClicked;
        public event Action<int> RemoveBeatClicked;

        private void removeButton_Click(object sender, EventArgs e)
        {
            if(seqDataGridView.SelectedCells.Count > 0)
            {
                foreach(DataGridViewCell cell in seqDataGridView.SelectedCells)
                {
                    cell.Style.BackColor = Color.White;
                    RemoveBeatClicked(cell.ColumnIndex);
                    recalculateColor(cell.RowIndex, cell.ColumnIndex);
                }
            }
        }

        private void recalculateColor(int row, int column)
        {
            if(row == 3)
            {
                seqDataGridView.Rows[0].Cells[column].Style.BackColor = Color.White;
                seqDataGridView.Rows[1].Cells[column].Style.BackColor = Color.White;
                seqDataGridView.Rows[2].Cells[column].Style.BackColor = Color.White;
            } else
            {
                int R, G, B;
                R = G = B = 0;
                R = seqDataGridView.Rows[0].Cells[column].Style.BackColor == Color.White ? 0 : seqDataGridView.Rows[0].Cells[column].Style.BackColor.R;
                G = seqDataGridView.Rows[1].Cells[column].Style.BackColor == Color.White ? 0 : seqDataGridView.Rows[1].Cells[column].Style.BackColor.G;
                B = seqDataGridView.Rows[2].Cells[column].Style.BackColor == Color.White ? 0 : seqDataGridView.Rows[2].Cells[column].Style.BackColor.B;
                seqDataGridView.Rows[3].Cells[column].Style.BackColor = R == 0 && G == 0 && B == 0 ? Color.White : Color.FromArgb(R,G,B);
            }
        }

        private void setColorButton_Click(object sender, EventArgs e)
        {
            colorDialog1.ShowDialog();
            colorPictureBox.BackColor = colorDialog1.Color;
        }

        private void seqDataGridView_SelectionChanged(object sender, EventArgs e)
        {
            if (seqDataGridView.SelectedCells.Count > 1)
            {
                var selected = seqDataGridView.SelectedCells;
                bool changeAll = false;
                bool isCRow = false;
                int selectedIndex = selected.Count - 1;

                if (selected[selectedIndex].Style.BackColor != seqDataGridView.DefaultCellStyle.BackColor)
                {
                    changeAll = true;

                    if (selected[selectedIndex].RowIndex == 3)
                        isCRow = true;

                    foreach (DataGridViewCell c in seqDataGridView.SelectedCells)
                    {
                        if (changeAll && c.RowIndex == selected[selectedIndex].RowIndex && c.RowIndex == selected[selectedIndex].RowIndex)
                        {
                            Color color = seqDataGridView.Rows[selected[selectedIndex].RowIndex].Cells[selected[selectedIndex].ColumnIndex].Style.BackColor;
                            if (!isCRow)
                                c.Style.BackColor = color;
                            else
                            {
                                int col = c.ColumnIndex;
                                c.Style.BackColor = selected[selectedIndex].Style.BackColor;
                                seqDataGridView.Rows[0].Cells[col].Style.BackColor = Color.FromArgb(color.R, 0, 0);
                                seqDataGridView.Rows[1].Cells[col].Style.BackColor = Color.FromArgb(0, color.G, 0);
                                seqDataGridView.Rows[2].Cells[col].Style.BackColor = Color.FromArgb(0, 0, color.B);
                                seqDataGridView.Rows[3].Cells[col].Style.BackColor = color;
                            }
                        } else
                        {
                            c.Style.BackColor = c.Style.BackColor;
                        }
                    }
                }
            }
        }

        // drag drop color

        private void colorPictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            colorPictureBox.DoDragDrop($"{colorPictureBox.BackColor.R} {colorPictureBox.BackColor.G} {colorPictureBox.BackColor.B}", DragDropEffects.Move | DragDropEffects.Move);
        }

        private void seqDataGridView_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.Text))
            {
                e.Effect = DragDropEffects.Move;
            } else
            {
                e.Effect = DragDropEffects.None;
            }
        }

        private void seqDataGridView_DragDrop(object sender, DragEventArgs e)
        {

            Point clientPoint = seqDataGridView.PointToClient(new Point(e.X, e.Y));

            if (e.Data.GetData(DataFormats.Text).ToString() == "B")
            {
                int column = seqDataGridView.HitTest(clientPoint.X, clientPoint.Y).ColumnIndex;
                int row = seqDataGridView.HitTest(clientPoint.X, clientPoint.Y).RowIndex;

                switch(row)
                {
                    case 0:
                        seqDataGridView.Rows[row].Cells[column].Style.BackColor = Color.Red;
                        break;
                    case 1:
                        seqDataGridView.Rows[row].Cells[column].Style.BackColor = Color.FromArgb(0, 255, 0);
                        break;
                    case 2:
                        seqDataGridView.Rows[row].Cells[column].Style.BackColor = Color.Blue;
                        break;
                    case 3:
                        seqDataGridView.Rows[0].Cells[column].Style.BackColor = Color.Red; //R
                        seqDataGridView.Rows[1].Cells[column].Style.BackColor = Color.FromArgb(0,255,0); //G
                        seqDataGridView.Rows[2].Cells[column].Style.BackColor = Color.Blue; //B
                        seqDataGridView.Rows[3].Cells[column].Style.BackColor = Color.White;
                        break;
                }
                recalculateColor(row, column);

            } else
            {

                int column = seqDataGridView.HitTest(clientPoint.X, clientPoint.Y).ColumnIndex;
                string[] rgbs = e.Data.GetData(DataFormats.Text).ToString().Split(null);

                seqDataGridView.Rows[0].Cells[column].Style.BackColor = Color.FromArgb(Int32.Parse(rgbs[0]), 0, 0); //R
                seqDataGridView.Rows[1].Cells[column].Style.BackColor = Color.FromArgb(0, Int32.Parse(rgbs[1]), 0); //G
                seqDataGridView.Rows[2].Cells[column].Style.BackColor = Color.FromArgb(0, 0, Int32.Parse(rgbs[2])); //B
                seqDataGridView.Rows[3].Cells[column].Style.BackColor = Color.FromArgb(Int32.Parse(rgbs[0]), Int32.Parse(rgbs[1]), Int32.Parse(rgbs[2]));
            }
        }

        private void colorPictureBox_DoubleClick(object sender, EventArgs e)
        {
            colorDialog1.ShowDialog();
            colorPictureBox.BackColor = colorDialog1.Color;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var popup = new AdvancedSettingsForm();
            popup.ShowDialog();
            if(popup.DialogResult == DialogResult.OK && seqDataGridView.SelectedCells.Count > 0)
            {
                for(int i = 0; i < seqDataGridView.SelectedCells.Count; i++)
                {
                    seqDataGridView.SelectedCells[i].Value = popup.mode == "Sine" ? new Bitmap(@"D:\Desktop\Active HW\Senior Project\sine_wave2.png") :
                                                                                new Bitmap(@"D:\Desktop\Active HW\Senior Project\square_wave.png");

                }
            }
        }

        // drag drop base
        private void basePictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            basePictureBox.DoDragDrop("B", DragDropEffects.Move | DragDropEffects.Move);
        }
    }
}
