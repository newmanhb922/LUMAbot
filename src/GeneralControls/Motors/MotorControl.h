#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <wiringPi.h>
#include <stdbool.h>

#define MOTOR_1_DIR         15
#define MOTOR_2_DIR         13
#define MOTOR_3_DIR         31
#define MOTOR_4_DIR         29

/// @brief Sets up the i/o pins for the motor direction outputs
void SetupMotors();

/// @brief Sets the motor direction of a motor
/// @param motorNum Number of the motor to set
/// @param forward direction, true for forward, false for reverse
void SetMotorDir(int motorNum, bool forward);

#endif