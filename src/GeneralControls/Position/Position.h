#ifndef POSITION_H
#define POSITION_H

#include "../Motors/MotorControl.h"
#include <math.h>
#include <signal.h>
#include <unistd.h>
#include "../../Controller/Controller.h"
#include "../../Sensors/Ultrasonic.h"
#include "../../MQTT_Comms/MQTTModule.h"

#define GEAR_RATIO              20.0f
#define WHEEL_DIAM              4.0f // inches
#define PI                      3.14159265f
#define COUNTS_PER_MOTOR_REV    28.0f

// position in inches
extern float curPositionX;
extern float curPositionY;
extern float targetPositionX;
extern float targetPositionY;

extern float motor1Power; // front left
extern float motor2Power; // front right
extern float motor3Power; // back right
extern float motor4Power; // back left

extern float lastMotor1Power;
extern float lastMotor2Power;
extern float lastMotor3Power;
extern float lastMotor4Power;

// wheel velocity in inches / second
extern float curVelocity1;
extern float curVelocity2;
extern float curVelocity3;
extern float curVelocity4;

extern bool motor1Dir;
extern bool motor2Dir;
extern bool motor3Dir;
extern bool motor4Dir;

void InitPosition();

void StartSamplingData();

void CalculateCurVelocity();

void CalculateCurPosition();

void CalculateMotorPowers();

void ReadData();

void CalculateMotorDir();

void BoundMotorPowers();

void ResetEncoderCounts();

void AccelMotorPowers();

/// dutyCycle can be positive or negative, positive means move motor forward, negative means move motor backward
void SetMotorSpeed(int motorNum, float DutyCycle);
#endif
