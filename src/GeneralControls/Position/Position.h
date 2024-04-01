#include "MotorControl.h"
#include <math.h>
#include <signal.h>
#include <unistd.h>
#include "Controller.h"
#include "Ultrasonic.h"
#include "MQTTModule.h"

#define GEAR_RATIO          15.0f
#define WHEEL_DIAM          4.0f // inches
#define PI                  3.14159265f

// position in inches
float curPositionX;
float curPositionY;
float targetPositionX;
float targetPositionY;

// position of each motor in inches, used to calculate velocity
float curPosition1;
float curPosition2;
float curPosition3;
float curPosition4;
// last position of each motor in inches, used to calculate velocity
float lastPosition1;
float lastPosition2;
float lastPosition3;
float lastPosition4;

float motor1Power; // front left
float motor2Power; // front right
float motor3Power; // back right
float motor4Power; // back left

float motorToWheelRatio;
float sqrt_2;

// whee velocity in inches / second
float curVelocity1;
float curVelocity2;
float curVelocity3;
float curVelocity4;

// last time we calculated motor velocity
int lastTime1;
int lastTime2;
int lastTime3;
int lastTime4;

unsigned char readDataCounter;

void InitPosition();

void StartSamplingData();

void CalculateCurVelocity();

void CalculateCurPosition();

void CalculateMotorPowers();