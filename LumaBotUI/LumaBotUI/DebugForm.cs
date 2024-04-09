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
        private delegate void DebugDelegate(string debugMsg);
        public DebugForm(MqttModule mqtt)
        {
            InitializeComponent();
            if (mqtt != null)
            {
                mqtt.DebugReceived += Mqtt_DebugReceived;
                mqtt.SubscribeToTopic(MqttModule.Topic.Debug.ToString());
            }
        }

        private void AddDebugMsg(string debugMsg)
        {
            string newLine = String.Format("{0} {1}{2}", DateTime.Now.ToString("MM/dd/yyyy HH:mm:ss"), debugMsg, Environment.NewLine);
            debugBox.AppendText(newLine);
        }
        private void Mqtt_DebugReceived(object sender, MqttModule.DebugEventArgs e)
        {
            this?.BeginInvoke(new DebugDelegate(AddDebugMsg), e.DebugMessage);
        }
    }
}
