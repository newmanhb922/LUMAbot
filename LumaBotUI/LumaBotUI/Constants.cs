using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LumaBotUI
{
    public class Constants
    {
        public const int MIN_STAGE_X = -14;
        public const int MIN_STAGE_Y = -14;
        public const int MAX_STAGE_X = 14;
        public const int MAX_STAGE_Y = 0;

        public const string ESTOP_COMMAND = "EStop";
        public const string ESTOP_RESET_COMMAND = "EStopReset";
        public const string ZERO_COMMAND = "Zero";
        public const string INIT_CONTROLLER_COMMAND = "InitController";

        public const string A_COORD = "(168,0)";
        public const string B_COORD = "(84,0)";
        public const string C_COORD = "(0,0)";
        public const string D_COORD = "(-84,0)";
        public const string E_COORD = "(-168,0)";
        public const string F_COORD = "(168,-84)";
        public const string G_COORD = "(84,-84)";
        public const string H_COORD = "(0,-84)";
        public const string J_COORD = "(-84,-84)";
        public const string K_COORD = "(-168,-84)";
        public const string L_COORD = "(168,-168)";
        public const string M_COORD = "(84,-168)";
        public const string N_COORD = "(0,-168)";
        public const string P_COORD = "(-84,-168)";
        public const string Q_COORD = "(-168,-168)";

        public const string AUTOMATED_MOVE_STR = "Automated_Move_State";
        public const string CONTROLLER_MOVE_STR = "Controller_Move_State";
        public const string STOP_STR = "Stop_State";
        public const string WAITING_STR = "Waiting_State";
        public const string E_STOP_STR = "E_Stop_State";
        public const string OBSTACLE_AVOIDANCE_STR = "Obstacle_Avoidance_State";
        public const string START_STR = "Start_State";
        public const string CONTROLLER_SPIN_STR = "Controller_Spin_State";
        public const string UNKNOWN_STR = "Unknown_State";

        public const string NO_IP_ADDR = "NO_IP_ADDR";
        public const string PI_LOCAL_NAME = "raspberrypi7";

        public const string CONNECTION_ERROR = "Error connecting to MQTT broker";
        public const string IP_ADDR_STATUS_ERROR = "Can't find PI's IP Address";

        public const string APP_NAME_STR = "WindowsApp";

        public const string CONNECTED_STR = "Connected";
    }
}
