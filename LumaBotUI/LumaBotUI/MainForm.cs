using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static LumaBotUI.Constants;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;


namespace LumaBotUI
{
    public partial class MainForm : Form
    {

        #region Types
        enum RobotStatus { Disconnected = 0, Idle = 1, Moving = 2}

        #endregion

        #region Private Fields

        private RobotStatus status;

        private PointF curLocation; // location of robot
        private PointF targetLocation; // location to send robot to

        private string ipAddress;

        private MqttModule mqtt;
        #endregion

        #region Delegates
        private delegate void LocationDelegate();
        #endregion

        #region Constructor
        public MainForm()
        {
            ipAddress = "192.168.1.134"; // maybe get this dynamically somehow?!
            InitializeComponent();
            ConnectToMqtt();
        }
        #endregion

        #region Private Methods
        private void ConnectToMqtt()
        {
            mqtt = new MqttModule(ipAddress);
            mqtt.LocationUpdated += Mqtt_LocationUpdated;

            // example for publishing a message
            //client.Publish("/home/temperature", Encoding.UTF8.GetBytes(strValue), MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE, false); 
        }

        private void LocationUpdate()
        {
            string locationStr = String.Format("{0:F2}, {0:F2}", curLocation.X, curLocation.Y);
            positionLabel.Text = locationStr;
            UpdateGraphicLocation();
        }

        private void UpdateGraphicLocation()
        {

        }
        private void UpdateStatus()
        {
            statusLabel.Text = StatusToText(status);
        }

        private string StatusToText(RobotStatus status)
        {
            string toReturn = String.Empty;
            switch (status)
            {
                case RobotStatus.Disconnected:
                    toReturn = DISCONNECTED_STR;
                    break;
                case RobotStatus.Idle:
                    toReturn = IDLE_STR;
                    break;
                case RobotStatus.Moving:
                    toReturn = MOVING_STR;
                    break;
            }
            return toReturn;
        }
        #endregion

        #region Event Handlers
        private void Mqtt_LocationUpdated(object sender, MqttModule.LocationEventArgs e)
        {
            curLocation = e.CurLocation;
            this.BeginInvoke(new LocationDelegate(LocationUpdate));
        }
        private void goButton_Click(object sender, EventArgs e)
        {
            mqtt.PublishMessage(MqttModule.Topic.Command.ToString(), "Go");
        }
        #endregion
    }
}
