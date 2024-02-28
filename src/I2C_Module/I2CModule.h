#include <wiringPiI2C.h>
#include <stdio.h>

// The SetPWM functions are not the only thing that needs to be done to move the motors
// The SetPWM function only controls the speed. The direction must be controlled by setting 
// The direction pin on the driver board to High or Low 
// (and that wouldn't be I2C so it wouldn't make sense to put it in this file)

// not sure what the Id's should be yet
#define PWM_BOARD_ID    0x00


// Motor data registers
// each PWM output has an "on" value and "off" value from 0 to 4095
// the 8 LSBs are in the _L register and 4 MSBs are in the _H register
#define MOTOR1_ON_L     0x06
#define MOTOR1_ON_H     0x07
#define MOTOR1_OFF_L    0x08
#define MOTOR1_OFF_H    0x09
#define MOTOR2_ON_L     0x0A
#define MOTOR2_ON_H     0x0B
#define MOTOR2_OFF_L    0x0C
#define MOTOR2_OFF_H    0x0D
#define MOTOR3_ON_L     0x0E
#define MOTOR3_ON_H     0x0F
#define MOTOR3_OFF_L    0x10
#define MOTOR3_OFF_H    0x11
#define MOTOR4_ON_L     0x12
#define MOTOR4_ON_H     0x13
#define MOTOR4_OFF_L    0x14
#define MOTOR4_OFF_H    0x15

// special registers
#define PRE_SCALE_REG   0xFE
#define MODE1_REG       0x00

// Mode 1 register bits
#define AUTO_INCR_BIT   0x05
#define SLEEP_BIT       0x04

/// @brief sets up I2C communication
/// @return returns -1 if there was an error
int SetupI2C();

/// @brief Turns specified motor off
/// @param motorNum motor to turn off
void TurnMotorOff(int motorNum);

/// @brief Sets the pwm for the specified motor
/// @param motorNum motor to set
/// @param dutyCycle dutycyle to set
void SetMotorPWM(int motorNum, float dutyCycle);

/// @brief turns Motor1 off
void Motor1Off();

/// @brief sets speed of Motor 1
/// @param dutyCycle duty cycle as a percentage
void Motor1SetPWM(float dutyCycle);

/// @brief turns Motor2 off
void Motor2Off();

/// @brief sets speed of Motor 2
/// @param dutyCycle duty cycle as a percentage
void Motor2SetPWM(float dutyCycle);

/// @brief turns Motor3 off
void Motor3Off();

/// @brief sets speed of Motor 3
/// @param dutyCycle duty cycle as a percentage
void Motor3SetPWM(float dutyCycle);

/// @brief turns Motor4 off
void Motor4Off();

/// @brief sets speed of Motor 4
/// @param dutyCycle duty cycle as a percentage
void Motor4SetPWM(float dutyCycle);
