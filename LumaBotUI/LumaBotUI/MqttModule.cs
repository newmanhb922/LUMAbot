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
    class MqttModule
    {
        #region Private Enums
        public enum Topic { CurrentPosition, TargetPosition, Command };
        #endregion

        #region Private Fields
        private MqttClient mqttClient;
        #endregion

        #region Constructor
        public MqttModule(string ipAddress)
        {
            mqttClient = new MqttClient(ipAddress);
            mqttClient.MqttMsgPublishReceived += MqttClient_MqttMsgPublishReceived;
            SubscribeToTopic(Topic.CurrentPosition.ToString());
            mqttClient.Connect("Windows PC");
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
        #endregion

        #region Public Methods
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
                    float xCoord = float.Parse(coords[0]);
                    float yCoord = float.Parse(coords[1]);
                    OnLocationUpdated(new LocationEventArgs(new PointF(xCoord, yCoord)));
                }
            }
        }
        #endregion
    }
}
