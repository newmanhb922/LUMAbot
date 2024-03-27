#include "../Motors/MotorControl.h"
#include <math.h>

#define GEAR_RATIO          15.0f
#define WHEEL_DIAM          4.0f
#define PI                  3.14159265f

float positionX;
float positionY;

float motorToWheelRatio;

void InitPosition();

void CalculatePosition();