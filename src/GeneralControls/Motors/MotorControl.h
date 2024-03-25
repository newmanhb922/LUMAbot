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
#define ENCODER_1A          30
#define ENCODER_1B          26
#define ENCODER_2A          23
#define ENCODER_2B          24
#define ENCODER_3A          27
#define ENCODER_3B          25
#define ENCODER_4A          28
#define ENCODER_4B          29

volatile unsigned char last1A;
volatile unsigned char last1B;
volatile unsigned char last2A;
volatile unsigned char last2B;
volatile unsigned char last3A;
volatile unsigned char last3B;
volatile unsigned char last4A;
volatile unsigned char last4B;

volatile int encoder1Count;
volatile int encoder2Count;
volatile int encoder3Count;
volatile int encoder4Count;

volatile bool count1Changing;
volatile bool count2Changing;
volatile bool count3Changing;
volatile bool count4Changing;

/// @brief Sets up the i/o pins for the motor direction outputs and sets up encoders
void SetupMotors();

/// @brief Sets the motor direction of a motor
/// @param motorNum Number of the motor to set
/// @param forward direction, true for forward, false for reverse
void SetMotorDir(int motorNum, bool forward);

#endif
