#include <wiringPiI2C.h>

// not sure what the Id's should be yet
#define MOTOR0_ID       0x00
#define MOTOR1_ID       0x01
#define MOTOR2_ID       0x02
#define MOTOR3_ID       0x03

// Motor data registers
// each PWM output has an "on" value and "off" value from 0 to 4095
// the 8 LSBs are in the _L register and 4 MSBs are in the _H register
#define MOTOR0_ON_L     0x06
#define MOTOR0_ON_H     0x07
#define MOTOR0_OFF_L    0x08
#define MOTOR0_OFF_H    0x09
#define MOTOR1_ON_L     0x0A
#define MOTOR1_ON_H     0x0B
#define MOTOR1_OFF_L    0x0C
#define MOTOR1_OFF_H    0x0D
#define MOTOR2_ON_L     0x0E
#define MOTOR2_ON_H     0x0F
#define MOTOR2_OFF_L    0x10
#define MOTOR2_OFF_H    0x11
#define MOTOR3_ON_L     0x12
#define MOTOR3_ON_H     0x13
#define MOTOR3_OFF_L    0x14
#define MOTOR3_OFF_H    0x15

/// @brief sets up I2C communication with all 4 motor drivers
/// @return returns -1 if there was an error
int SetupI2C();

/// @brief turns Motor0 off
void Motor0Off();

/// @brief sets speed of Motor 0
/// @param dutyCycle duty cycle as a percentage
void Motor0SetSpeed(float dutyCycle);

/// @brief turns Motor1 off
void Motor1Off();

/// @brief sets speed of Motor 1
/// @param dutyCycle duty cycle as a percentage
void Motor1SetSpeed(float dutyCycle);

/// @brief turns Motor2 off
void Motor2Off();

/// @brief sets speed of Motor 2
/// @param dutyCycle duty cycle as a percentage
void Motor2SetSpeed(float dutyCycle);

/// @brief turns Motor3 off
void Motor3Off();

/// @brief sets speed of Motor 3
/// @param dutyCycle duty cycle as a percentage
void Motor3SetSpeed(float dutyCycle);

/// @brief turns the specified motor off
/// @param motorID motor id
/// @param motorOffHAddress address of the OFF_H register for this motor
void MotorOff(int motorID, int motorOffHAddress);

/// @brief sets speed of a specified motor
/// @param motorID motor id
/// @param motorOnLAddress address of the ON_L register for this motor
/// @param dutyCycle duty cycle as a percentage
void MotorSetSpeed(int motorID, int motorOnLAddress, float dutyCycle);