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

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        SerialPort port;

        public Form1()
        {
            InitializeComponent();

            String[] ports = SerialPort.GetPortNames();
            foreach (String s in ports)
            {
                portsBox.Items.Add(s);
            }
        }

        private void connectButton_Click(object sender, EventArgs e)
        {
            if (connectButton.Text != "Disconnect")
            {
                string selectedPort = portsBox.SelectedItem.ToString();
                port = new SerialPort(selectedPort, 9600, Parity.None, 8, StopBits.One);
                port.DataReceived += SerialPortDataReceived;
                port.Open();
                port.Write("!.");
                connectButton.Text = "Disconnect";
            } else
            {
                port.Write("R255.");
                port.Write("G255.");
                port.Write("B255.");
                port.Write("?.");
                port.Close();
                connectButton.Text = "Connect";
            }
        }

        private void SerialPortDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort p = (SerialPort)sender;
            //numberLabel.Text = p.ReadExisting();
        }

        private void rCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (!rCheckBox.Checked)
                port.Write("R0.");
            else
                port.Write("R254.");
        }

        private void gCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (!gCheckBox.Checked)
                port.Write("G0" + '.');
            else
                port.Write("G254" + '.');
        }

        private void bCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (!bCheckBox.Checked)
                port.Write("B0.");
            else
                port.Write("B254.");
        }

        private void rTrackBar_Scroll(object sender, EventArgs e)
        {
            double strength = 255 - (rTrackBar.Value * 10 * 255 / 100);
            rStrengthLabel.Text = (255 + (strength * -1)).ToString();
            port.Write("R" + strength + '.');
        }

        private void gTrackBar_Scroll(object sender, EventArgs e)
        {
            double strength = 255 - (gTrackBar.Value * 10 * 255 / 100);
            gStrengthLabel.Text = (255 + (strength*-1)).ToString();
            port.Write("G" + strength + '.');
        }

        private void bTrackBar_Scroll(object sender, EventArgs e)
        {
            double strength = 255 - (bTrackBar.Value * 10 * 255 / 100);
            bStrengthLabel.Text = (255 + (strength * -1)).ToString();
            port.Write("B" + strength + '.');
        }
    }


}
