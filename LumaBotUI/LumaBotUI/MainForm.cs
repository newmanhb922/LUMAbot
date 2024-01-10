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
using MQTTnet.Server;
using MQTTnet;
using MQTTnet.Protocol;
using MQTTnet.Diagnostics;

namespace LumaBotUI
{
    public partial class MainForm : Form
    {

        #region Types

        enum RobotStatus { Disconnected = 0, Idle = 1, Moving = 2}

        #endregion

        #region Variables

        private RobotStatus status;

        #endregion

        #region Constructor

        public MainForm()
        {
            InitializeComponent();
        }

        #endregion

        #region Private Methods
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

        #endregion

    }
}
