#include "Controller.h"

int fileDescrip;

void ReadEvents();

int InitController()
{
    fileDescrip = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
    signal(SIGALRM, ReadEvents);
    ualarm(1000, 1000);
}

void ReadEvents(int sigNum)
{
    struct js_event e;
    if (read(fileDescrip, &e, sizeof(e)) == sizeof(e))
    { // event read
        if (e.type == JS_EVENT_AXIS)
        { // joystick moved
            printf("moving axis number %d to value %d\n", e.number, e.value);
        }
    }
}
