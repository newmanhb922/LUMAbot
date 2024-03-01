using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LumaBotUI
{
    public partial class DebugForm : Form
    {
        private MqttModule mqttModule;
        public DebugForm(MqttModule mqtt)
        {
            InitializeComponent();
            if (mqtt != null)
            {
                mqtt.DebugReceived += Mqtt_DebugReceived;
            }
        }

        private void Mqtt_DebugReceived(object sender, MqttModule.DebugEventArgs e)
        {
            string newLine = String.Format("{0} {1}\n", DateTime.Now.ToString("MM/dd/yyyy H:mm:ss"), e.DebugMessage);
            debugBox.AppendText(newLine);
        }
    }
}
