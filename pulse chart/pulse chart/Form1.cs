using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Windows.Forms.DataVisualization.Charting;

namespace pulse_chart
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public void tcp()
        {
            int i = 0;
            TcpClient client1 = new TcpClient("http://192.168.1.70", 70);
            NetworkStream nwStream = client1.GetStream();
            nwStream = client1.GetStream();
            while (true)
            {
                if (nwStream.DataAvailable)
                {
                    byte[] bytesToRead = new byte[client1.ReceiveBufferSize];
                    int bytesRead = nwStream.Read(bytesToRead, 0, client1.ReceiveBufferSize);
                    string r = Encoding.ASCII.GetString(bytesToRead, 0, bytesRead);
                    //15
                    string[] a = r.Split(',');
                    foreach (var item in a)
                    {
                        if (!item.Contains("_Y") && !item.Contains("_WI"))
                        {
                            i++;
                            chart1.Invoke(new Action(() =>
                            {
                                chart1.Series[0].Points.AddXY(i, item);
                                if (chart1.Series[0].Points.Count > 1000)
                                {
                                    chart1.Series[0].Points.Remove(chart1.Series[0].Points[0]);
                                    chart1.ChartAreas[0].AxisX.Minimum = chart1.Series[0].Points[0].XValue;
                                    chart1.ChartAreas[0].AxisX.Maximum = i;
                                }
                            }));
                        }
                        else if (item.Contains("_Y"))
                        {
                            label2.Invoke(new Action(() => label2.Text = item.Replace("_Y", "")));
                        }
                        else if (item.Contains("_WI"))
                        {
                            label4.Invoke(new Action(() => label4.Text = item.Replace("_WI", "")));
                        }
                    }
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            chart1.Series[0].ChartType = SeriesChartType.Line;
            chart1.Series[0].Color = Color.Red;
            //chart1.ChartAreas[0].AxisX.MajorGrid.Enabled = false;
            //chart1.ChartAreas[0].AxisY.MajorGrid.Enabled = false;
            new Task(tcp).Start();
        }
    }
}
