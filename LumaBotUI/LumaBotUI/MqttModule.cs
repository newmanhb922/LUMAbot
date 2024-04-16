using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using System.Drawing;

namespace LumaBotUI
{
    public class MqttModule
    {
        #region Private Enums
        public enum Topic { CurrentPosition, TargetPosition, Command, Debug, State };
        #endregion

        #region Private Fields
        private MqttClient mqttClient;
        #endregion

        #region Constructor
        public MqttModule(string ipAddress)
        {
            mqttClient = new MqttClient(ipAddress, 5900, false, null, null, MqttSslProtocols.None);
            mqttClient.MqttMsgPublishReceived += MqttClient_MqttMsgPublishReceived;
        }
        #endregion

        #region Events
        public event EventHandler<LocationEventArgs> LocationUpdated;

        public class LocationEventArgs : EventArgs
        {
            public PointF CurLocation { get; set; }

            public LocationEventArgs(PointF location)
            {
                CurLocation = location;
            }
        }

        protected virtual void OnLocationUpdated(LocationEventArgs e)
        {
            LocationUpdated?.Invoke(this, e);
        }

        public event EventHandler<StatusEventArgs> StatusUpdated;

        public class StatusEventArgs : EventArgs
        {
            public string Status { get; set; }
            public StatusEventArgs(string status)
            {
                Status = status;
            }
        }

        protected virtual void OnStatusUpdate(StatusEventArgs e)
        {
            StatusUpdated?.Invoke(this, e);
        }

        public event EventHandler<DebugEventArgs> DebugReceived;

        public class DebugEventArgs : EventArgs
        {
            public string DebugMessage { get; set; }
            public DebugEventArgs(string debugMessage)
            {
                DebugMessage = debugMessage;
            }
        }

        protected virtual void OnDebugReceived(DebugEventArgs e)
        {
            DebugReceived?.Invoke(this, e);
        }
        #endregion

        #region Public Methods
        public void ConnectToBroker()
        {
            byte returnCode = 1;
            try
            {
                returnCode = mqttClient.Connect("WindowsApp");
            }
            catch (Exception e)
            {
                //error
                OnStatusUpdate(new StatusEventArgs("Error connecting to MQTT broker"));
            }
            if (returnCode == 0)
            {
                OnStatusUpdate(new StatusEventArgs("Connected"));
            }
        }
        public void SubscribeToTopic(string topic)
        {
            mqttClient.Subscribe(new string[] { topic }, new byte[] { MqttMsgBase.QOS_LEVEL_AT_LEAST_ONCE });
        }
        public void PublishMessage(string topic, string message)
        {
            mqttClient.Publish(topic, Encoding.UTF8.GetBytes(message), MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE, false);
        }
        #endregion

        #region Event Handlers
        private void MqttClient_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
        {
            string msg = Encoding.UTF8.GetString(e.Message);

            if (e.Topic == Topic.CurrentPosition.ToString())
            {
                string[] coords = msg.Split(',');
                if (coords.Length == 2)
                {
                    float xCoord = float.Parse(coords[0]) / 12.0f;
                    float yCoord = float.Parse(coords[1]) / 12.0f;
                    OnLocationUpdated(new LocationEventArgs(new PointF(xCoord, yCoord)));
                }
            }
            else if (e.Topic == Topic.Debug.ToString())
            {
                OnDebugReceived(new DebugEventArgs(msg));
            }
            else if (e.Topic == Topic.State.ToString())
            {
                OnStatusUpdate(new StatusEventArgs(msg));
            }
        }
        #endregion
    }
}
