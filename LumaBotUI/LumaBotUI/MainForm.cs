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

        private DebugForm debugForm;

        private bool eStopPressed;
        #endregion

        #region Delegates
        private delegate void LocationDelegate();
        private delegate void StatusDelegate(string status);
        #endregion

        #region Constructor
        public MainForm()
        {
            ipAddress = "192.168.43.65"; // maybe get this dynamically somehow?!
            //ipAddress = "172.30.233.63";
            InitializeComponent();
            eStopPressed = false;
        }
        #endregion

        #region Private Methods
        private void ConnectToMqtt()
        {
            mqtt = new MqttModule(ipAddress);
            mqtt.LocationUpdated += Mqtt_LocationUpdated;
            mqtt.StatusUpdated += Mqtt_StatusUpdated;
            mqtt.SubscribeToTopic(MqttModule.Topic.CurrentPosition.ToString());
            mqtt.ConnectToBroker();
            // example for publishing a message
            //client.Publish("/home/temperature", Encoding.UTF8.GetBytes(strValue), MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE, false); 
        }



        private void LocationUpdate()
        {
            positionLabel.Text = String.Format("{0:F2}, {1:F2}", curLocation.X, curLocation.Y);
            UpdateGraphicLocation();
        }
        private void StatusUpdate(string status)
        {
            statusLabel.Text = status;
        }
        private void UpdateGraphicLocation()
        {
            PointF topLeftPoint = new PointF(stageGrid.Left + stageLocationL.Width / 2,
                                        stageGrid.Top + stageLocationL.Height / 2);
            PointF bottomRightPoint = new PointF(topLeftPoint.X + 4 * stageLocationL.Width,
                                            topLeftPoint.Y + 2 * stageLocationL.Height);
            float stageToFormRatioX = -(bottomRightPoint.X - topLeftPoint.X) / (MAX_STAGE_X - MIN_STAGE_X);
            float stageToFormRatioY = (bottomRightPoint.Y - topLeftPoint.Y) / (MAX_STAGE_Y - MIN_STAGE_Y);

            float positionBoxCenterX = ((curLocation.X * stageToFormRatioX) + 2.5f * stageLocationL.Width + stageGrid.Left + stageLocationL.Margin.Left + 1);
            float positionBoxCenterY = ((curLocation.Y * stageToFormRatioY) + 2.5f * stageLocationL.Height + stageGrid.Top + stageLocationL.Margin.Top + 3);

            positionBoxCenterX = AdjustXForMargins(positionBoxCenterX);
            positionBoxCenterY = AdjustYForMargins(positionBoxCenterY);

            robotPositionBox.Location = new Point((int)(positionBoxCenterX - robotPositionBox.Width / 2.0),
                                                  (int)(positionBoxCenterY - robotPositionBox.Height / 2.0));
            stageGrid.Refresh();
            robotPositionBox.Refresh();
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
        private float AdjustXForMargins(float xCoord)
        {
            if (xCoord > stageLocationL.Width * 4)
            {
                xCoord = xCoord + stageLocationL.Margin.Left * 8;
            }
            else if (xCoord > stageLocationL.Width * 3)
            {
                xCoord = xCoord + stageLocationL.Margin.Left * 6;
            }
            else if (xCoord > stageLocationL.Width * 2)
            {
                xCoord = xCoord + stageLocationL.Margin.Left * 4;
            }
            else if (xCoord > stageLocationL.Width)
            {
                xCoord = xCoord + stageLocationL.Margin.Left * 2;
            }
            return xCoord;
        }
        private float AdjustYForMargins(float yCoord)
        {
            if (yCoord > stageLocationL.Height * 2)
            {
                yCoord = yCoord + stageLocationL.Margin.Top * 4;
            }
            else if (yCoord > stageLocationL.Height)
            {
                yCoord = yCoord + stageLocationL.Margin.Top * 2;
            }
            return yCoord;
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
            string coordToSend = C_COORD;
            switch (pointSelectionCombo.SelectedItem.ToString())
            {
                case "A":
                    coordToSend = A_COORD;
                    break;
                case "B":
                    coordToSend = B_COORD;
                    break;
                case "C":
                    coordToSend = C_COORD;
                    break;
                case "D":
                    coordToSend = D_COORD;
                    break;
                case "E":
                    coordToSend = E_COORD;
                    break;
                case "F":
                    coordToSend = F_COORD;
                    break;
                case "G":
                    coordToSend = G_COORD;
                    break;
                case "H":
                    coordToSend = H_COORD;
                    break;
                case "J":
                    coordToSend = J_COORD;
                    break;
                case "K":
                    coordToSend = K_COORD;
                    break;
                case "L":
                    coordToSend = L_COORD;
                    break;
                case "M":
                    coordToSend = M_COORD;
                    break;
                case "N":
                    coordToSend = N_COORD;
                    break;
                case "P":
                    coordToSend = P_COORD;
                    break;
                case "Q":
                    coordToSend = Q_COORD;
                    break;
            }
            mqtt.PublishMessage(MqttModule.Topic.TargetPosition.ToString(), coordToSend);
        }
        private void Mqtt_StatusUpdated(object sender, MqttModule.StatusEventArgs e)
        {
            this.BeginInvoke(new StatusDelegate(StatusUpdate), e.Status);
        }
        private void MainForm_Load(object sender, EventArgs e)
        {
            ConnectToMqtt();
            LocationUpdate();
        }
        private void eStopButton_Click(object sender, EventArgs e)
        {
            if (!eStopPressed) // e stop hasn't been pressed yet, tell pi to stop
            {
                mqtt.PublishMessage(MqttModule.Topic.Command.ToString(), ESTOP_COMMAND);
                eStopPressed = true;
                eStopButton.Text = "Reset EStop";
            }
            else // e stop already pressed, tell pi we can go again
            {
                mqtt.PublishMessage(MqttModule.Topic.Command.ToString(), ESTOP_RESET_COMMAND);
                eStopPressed = false;
                eStopButton.Text = "Emergency Stop";
            }
        }
        #endregion

        private void launchDebugButton_Click(object sender, EventArgs e)
        {
            if (debugForm == null)
            {
                debugForm = new DebugForm(mqtt);
            }
            debugForm.Show();
        }

        private void setOriginButton_Click(object sender, EventArgs e)
        {
            string message = "Are you sure you want to set the robot's current position as the (0, 0) position (origin)?";
            if (MessageBox.Show(message, "Are you sure?", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                mqtt.PublishMessage(MqttModule.Topic.Command.ToString(), ZERO_COMMAND);
            }
        }
    }
}
