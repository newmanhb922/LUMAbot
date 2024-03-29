using System;
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
    }
}
