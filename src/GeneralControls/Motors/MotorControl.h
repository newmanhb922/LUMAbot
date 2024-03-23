#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <wiringPi.h>
#include <stdbool.h>
#include <stdio.h>

// these are the wiringPi pin definitions.
// see pinout.xyz/pinout/wiringpi for the corresponding rpi gpio pins
#define MOTOR_1_DIR         3
#define MOTOR_2_DIR         2
#define MOTOR_3_DIR         22
#define MOTOR_4_DIR         21

/// @brief Sets up the i/o pins for the motor direction outputs
void SetupMotors();

/// @brief Sets the motor direction of a motor
/// @param motorNum Number of the motor to set
/// @param forward direction, true for forward, false for reverse
void SetMotorDir(int motorNum, bool forward);

#endif
