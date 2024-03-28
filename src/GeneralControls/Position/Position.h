#include "../Motors/MotorControl.h"
#include <math.h>

#define GEAR_RATIO          15.0f
#define WHEEL_DIAM          4.0f // inches
#define PI                  3.14159265f

// position in inches
float curPositionX;
float curPositionY;
float targetPositionX;
float targetPositionY;
float motor1Power; // front left
float motor2Power; // front right
float motor3Power; // back right
float motor4Power; // back left

float motorToWheelRatio;

void InitPosition();

void CalculateCurPosition();

void CalculateMotorPowers();