#include "Controller.h"

int fileDescrip;
extern short controllerXValue;
extern short controllerYValue;

void InitController()
{
    fileDescrip = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
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
                printf("setting controllerXValue to %d\n", e.value);
                controllerXValue = e.value;
            }
            else if (e.number == 1)
            {
                printf("setting controllerYValue to %d\n", e.value);
                controllerYValue = e.value;
            }
        }
    }
}
