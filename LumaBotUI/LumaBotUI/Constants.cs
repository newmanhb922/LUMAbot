﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LumaBotUI
{
    public class Constants
    {
        // States strings
        public const string DISCONNECTED_STR = "Disconnected";
        public const string IDLE_STR = "Idle";
        public const string MOVING_STR = "Moving";

        public const int MIN_STAGE_X = -14;
        public const int MIN_STAGE_Y = -14;
        public const int MAX_STAGE_X = 14;
        public const int MAX_STAGE_Y = 0;

        public const string ESTOP_COMMAND = "EStop";
        public const string ESTOP_RESET_COMMAND = "EStopReset";
        public const string ZERO_COMMAND = "Zero";

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
    }
}
