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
    public partial class AdvancedSettingsForm : Form
    {
        public int rate = 5;
        public string mode = "square";
        public bool wasComplete = false;

        public AdvancedSettingsForm()
        {
            InitializeComponent();
            modeComboBox.Text = "square";
        }

        public AdvancedSettingsForm(int rate, string mode)
        {
            InitializeComponent();
            modeComboBox.Text = mode;
            numericUpDown1.Value = rate;

            this.rate = rate;
            this.mode = mode;
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            rate = (int)numericUpDown1.Value;
        }

        private void modeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            mode = modeComboBox.Text;
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {

            wasComplete = false;
            this.Close();
        }
    }
}
