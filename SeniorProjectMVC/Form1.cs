using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SeniorProjectMVC
{
    public partial class Form1 : Form, IColorGuru
    {
        public Color ColorAdder
        {
            set
            {
                ListViewItem item = new ListViewItem();
                item.BackColor = value;
                colorListView.Items.Add(item);
            }
        }

        public int DurationLoader
        {
            set
            {
                durationLabel.Text = value.ToString();
                durationTrackBar.Value = value / 5;
            }
        }

        private int iter;

        public Form1()
        {
            iter = 0;

            InitializeComponent();
            colorListView.ItemSelectionChanged += colorListView_ItemSelectionChanged;

            String[] ports = SerialPort.GetPortNames();
            foreach (String s in ports)
            {
                portComboBox.Items.Add(s);
            }
        }

        public event Action<Color, int> AddColorClicked;
        public event Action<int> RemoveColorClicked;
        public event Action SavePatternClicked;
        public event Action<int> DeletePatternClicked;
        public event Action<int, int> DurationChanged;
        public event Action<Color, int> ColorChanged;
        public event Action<int> LoadPatternClicked;
        public event Action<int> AddPatternButtonClicked;
        public event Action<int> RemovePatternButtonClicked;
        public event Action<int> ColorSelectionChanged;
        public event Action<string> ExportButtonClicked;
        public event Action<string> ConnectButtonClicked;
        public event Action DisconnectButtonClicked;

        private void selectColorButton_Click(object sender, EventArgs e)
        {
            colorDialog1.ShowDialog();
            selectedColorBox.BackColor = colorDialog1.Color;
            if(colorListView.SelectedItems.Count > 0)
            {
                colorListView.SelectedItems[0].BackColor = colorDialog1.Color;
                ColorChanged(colorDialog1.Color, colorListView.SelectedItems[0].Index);
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            int duration = (durationTrackBar.Value * 5);
            durationLabel.Text = (durationTrackBar.Value * 5).ToString();
            if (colorListView.SelectedItems.Count > 0)
                DurationChanged(duration, colorListView.SelectedItems[0].Index);
        }

        private void colorListView_ItemSelectionChanged(object sender, EventArgs e)
        {
            if(colorListView.SelectedItems.Count > 0)
            {
                selectedColorBox.BackColor = colorListView.SelectedItems[0].BackColor;
                ColorSelectionChanged(colorListView.SelectedItems[0].Index);
            }
        }

        private void removeColor_Click(object sender, EventArgs e)
        {
            if(colorListView.SelectedItems.Count > 0)
            {
                RemoveColorClicked(colorListView.SelectedItems[0].Index);
                colorListView.SelectedItems[0].Remove();
            }
            else if (colorListView.Items.Count > 0)
            {
                RemoveColorClicked(colorListView.Items.Count - 1);
                colorListView.Items.Remove(colorListView.Items[colorListView.Items.Count - 1]);
            }
        }

        private void addColor_Click(object sender, EventArgs e)
        {
            ListViewItem item = new ListViewItem();
            item.SubItems.Add("");
            item.BackColor = selectedColorBox.BackColor;

            colorListView.Items.Add(item);
            int duration = Int32.Parse(durationLabel.Text);
            AddColorClicked(selectedColorBox.BackColor , duration);
        }

        private void savePatternButton_Click(object sender, EventArgs e)
        {
            if(patternNameTextBox.Text == "")
            {
                patternNameTextBox.Text = iter.ToString();
                iter++;
            }
            SavePatternClicked();
            patternsListView.Items.Add(new ListViewItem(patternNameTextBox.Text));
            patternNameTextBox.Text = "";
            colorListView.Items.Clear();
        }

        private void deletePatternButton_Click(object sender, EventArgs e)
        {
            if(patternsListView.SelectedItems.Count > 0)
            {
                DeletePatternClicked(patternsListView.SelectedItems[0].Index);
                patternsListView.SelectedItems[0].Remove();
            } else if(patternsListView.Items.Count > 0)
            {
                DeletePatternClicked(patternsListView.Items.Count - 1);
                patternsListView.Items.RemoveAt(patternsListView.Items.Count - 1);
            }
        }

        private void loadPatternButton_Click(object sender, EventArgs e)
        {
            if(patternsListView.SelectedItems.Count > 0)
            {
                colorListView.Items.Clear();
                patternNameTextBox.Text = patternsListView.SelectedItems[0].Text;
                LoadPatternClicked(patternsListView.SelectedItems[0].Index);
                patternsListView.SelectedItems[0].Remove();
            }
        }

        private void addPatternButton_Click(object sender, EventArgs e)
        {
            if(patternsListView.SelectedItems.Count > 0)
            {
                ListViewItem selectedItem = patternsListView.SelectedItems[0];
                ListViewItem item = new ListViewItem(selectedItem.Text);
                setListView.Items.Add(item);
                AddPatternButtonClicked(selectedItem.Index);
                selectedItem.Remove();
            }
        }

        private void removePatternButton_Click(object sender, EventArgs e)
        {
            if(setListView.SelectedItems.Count > 0)
            {
                ListViewItem selected = setListView.SelectedItems[0];
                RemovePatternButtonClicked(selected.Index);
                selected.Remove();
                patternsListView.Items.Add(selected);
            }
        }

        private void exportButton_Click(object sender, EventArgs e)
        {
            if(setListView.Items.Count > 0)
            {
                SaveFileDialog saveDialog = new SaveFileDialog();
                saveDialog.Filter = "JSON (*.json)|*.json";
                if(saveDialog.ShowDialog() == DialogResult.OK)
                {
                    ExportButtonClicked(saveDialog.FileName);
                }
            }
        }

        private void connectButton_Click(object sender, EventArgs e)
        {
            if(portComboBox.Text.Length > 0 && connectButton.Text == "Connect")
            {
                ConnectButtonClicked(portComboBox.Text);
                connectButton.Text = "Disconnect";
            } else if (connectButton.Text == "Disconnect")
            {
                DisconnectButtonClicked();
                connectButton.Text = "Connect";
            }
        }
    }
}
