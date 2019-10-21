using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SGT_Debugger
{
    public partial class Form1 : Form
    {
        bool firstStart = true;
        public Form1()
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            InitializeComponent();
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
            foreach(string port in ports)
            {
                comboBoxCOM.Items.Add(port);
            }
            Display.Series[0].Points.AddY(12);
            Display.Series[0].Points.AddY(8);
            Display.Series[0].Points.AddY(15);
            Display.Series[0].Points.AddY(9);
            Display.Series[0].Points.AddY(5);
            Display.Series[1].Points.AddY(0);
            Display.Series[1].Points.AddY(8);
            Display.Series[1].Points.AddY(5);
            Display.Series[1].Points.AddY(9);
            Display.Series[1].Points.AddY(5);
            Display.Series[2].Points.AddY(9);
            Display.Series[2].Points.AddY(0);
            Display.Series[2].Points.AddY(5);
            Display.Series[2].Points.AddY(9);
            Display.Series[2].Points.AddY(0);

        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            seriousnum = trackBar1.Value;
            switch(trackBar1.Value)
            {
                case 1:
                    textBox1.Visible = true;  Display.Series[0].Enabled = true;
                    textBox2.Visible = false; Display.Series[1].Enabled = false;
                    textBox3.Visible = false; Display.Series[2].Enabled = false;
                    break;
                case 2:
                    textBox1.Visible = true;  Display.Series[0].Enabled = true; 
                    textBox2.Visible = true;  Display.Series[1].Enabled = true; 
                    textBox3.Visible = false; Display.Series[2].Enabled = false;
                    break;
                case 3:
                    textBox1.Visible = true;  Display.Series[0].Enabled = true;
                    textBox2.Visible = true;  Display.Series[1].Enabled = true;
                    textBox3.Visible = true;  Display.Series[2].Enabled = true;
                    break;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(button1.Text == "打开串口")
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
                catch(ArgumentException exc)
                {
                    MessageBox.Show(exc.Message);
                    return;
                }
                if(COMPort.IsOpen)
                {
                    MessageBox.Show("打开成功");
                    string s = "SGT_Debuger Online";
                    byte[] buf = Encoding.ASCII.GetBytes(s);
                    COMPort.Write(buf, 0, s.Length);
                    button1.Text = "关闭串口";
                }
                else
                {
                    MessageBox.Show("存在问题");
                }
            }
            else
            {
                string s = "SGT_Debuger Offline";
                byte[] buf = Encoding.ASCII.GetBytes(s);
                COMPort.Write(buf, 0, s.Length);
                COMPort.Close();
                button1.Text = "打开串口";
            }
            
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            Display.Series[0].LegendText = textBox1.Text;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            Display.Series[1].LegendText = textBox2.Text;
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            Display.Series[2].LegendText = textBox3.Text;
        }

        int value = 0;
        int countByte = 0;
        int seriousCount = 0;
        int length = 1;
        int seriousnum = 1;
        private void COMPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            if(firstStart)
            {
                Display.Series[0].Points.Clear();
                Display.Series[1].Points.Clear();
                Display.Series[2].Points.Clear();
                firstStart = false;
            }
            if(NumMode.Checked==false)
            {
                byte[] buf = new byte[COMPort.BytesToRead];
                COMPort.Read(buf, 0, buf.Length);
                foreach (Byte mes in buf)
                {
                    countByte++;
                    value = value << 8 | mes;
                    if (countByte == length)
                    {
                        //Display.Series[seriousCount].Points.AddY(value);
                        this.Invoke(new Action(() =>
                        {
                            Display.Series[seriousCount].Points.AddY(value);
                        }));
                        value = 0;
                        seriousCount++;
                        countByte = 0;
                    }
                    if (seriousCount == seriousnum)
                    {
                        seriousCount = 0;
                    }
                }
            }
            else
            {
                byte[] buf = new byte[COMPort.BytesToRead];
                COMPort.Read(buf, 0, buf.Length);
                foreach (Byte mes in buf)
                {
                    countByte++;
                    value = value * 10 + (mes-'0');
                    if (countByte == length)
                    {
                        //Display.Series[seriousCount].Points.AddY(value);
                        this.Invoke(new Action(() =>
                        {
                            Display.Series[seriousCount].Points.AddY(value);
                        }));
                        value = 0;
                        seriousCount++;
                        countByte = 0;
                    }
                    if (seriousCount == seriousnum)
                    {
                        seriousCount = 0;
                    }
                }
            }
            
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            length = trackBar2.Value;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form2 form = new Form2();
            form.Show();
        }
    }
}
