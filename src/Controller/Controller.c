#include "Controller.h"

int fileDescrip;

void InitController()
{
    fileDescrip = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
}

void ReadJoystickEvents()
{
    struct js_event e;
    if (read(fileDescrip, &e, sizeof(e)) == sizeof(e))
    { // event read
        if (e.type == JS_EVENT_AXIS)
        { // joystick moved
            printf("moving axis number %d to value %d\n", e.number, e.value);
            if(e.number == 0)
            {
                xValue = e.value;
            }
            else if (e.number == 1)
            {
                yValue = e.value
            }
        }
    }
}
