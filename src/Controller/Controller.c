#include "Controller.h"

int fileDescrip;
short controllerXValue;
short controllerYValue;
bool controllerConnected;

void InitController()
{
    controllerConnected = false;
    int startTime = micros();
    fileDescrip = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
    if (fileDescrip != -1)
    {
        controllerConnected = true;
    }
}

void ReadJoystickData()
{
    struct js_event e;
    if (read(fileDescrip, &e, sizeof(e)) == sizeof(e))
    { // event read
        if (e.type == JS_EVENT_AXIS)
        { // joystick moved
            if(e.number == 0)
            {
                controllerXValue = e.value;
            }
            else if (e.number == 1)
            {
                controllerYValue = e.value * -1; // moving joystick down gives a positive value, we want that to be negative.
            }
        }
    }
}
