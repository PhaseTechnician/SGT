﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SGT_Debugger
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
            foreach (string port in ports)
            {
                comboBoxCOM.Items.Add(port);
            }
        }

        private void SendOut(char[] message)
        {
            COMPort.Write(message, 0, 5);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            char[] message = { '1','0', '0', '0',' '};
            NUM1.Text = trackBar1.Value.ToString();
            SendOut(message);
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            char[] message = { '2', '0', '0', '0', ' ' };
            NUM2.Text = trackBar2.Value.ToString();
            SendOut(message);
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            char[] message = { '3', '0', '0', '0', ' ' };
            NUM3.Text = trackBar3.Value.ToString();
            SendOut(message);
        }

        private void trackBar4_Scroll(object sender, EventArgs e)
        {
            char[] message = { '4', '0', '0', '0', ' ' };
            NUM4.Text = trackBar4.Value.ToString();
            SendOut(message);
        }

        private void trackBar5_Scroll(object sender, EventArgs e)
        {
            char[] message = { '5', '0', '0', '0', ' ' };
            NUM5.Text = trackBar5.Value.ToString();
            SendOut(message);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (comboBoxBaudRate.SelectedIndex == 1)
                COMPort.BaudRate = 115200;
            else
                COMPort.BaudRate = 9600;
            try
            {
                COMPort.PortName = comboBoxCOM.Text;
                COMPort.Open();
            }
            catch (ArgumentException exc)
            {
                MessageBox.Show(exc.Message);
                return;
            }
        }

        private void COMPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            labelMES.Text = COMPort.ReadExisting();
        }
    }
}
