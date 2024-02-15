#include "I2CModule.h"

/// @brief turns the specified motor off
/// @param motorID motor id
/// @param motorOffHAddress address of the OFF_H register for this motor
void MotorOff(int motorID, int motorOffHAddress);

/// @brief sets speed of a specified motor
/// @param motorID motor id
/// @param motorOnLAddress address of the ON_L register for this motor
/// @param dutyCycle duty cycle as a percentage
void MotorSetSpeed(int motorID, int motorOnLAddress, float dutyCycle);

int SetupI2C()
{
    int status = 0;
    status  = wiringPiI2CSetup(MOTOR0_ID);
    if (status == -1)
    {
        printf("Motor0 I2C not connected\n");
    }
    status  = wiringPiI2CSetup(MOTOR1_ID);
    if (status == -1)
    {
        printf("Motor1 I2C not connected\n");
    }
    status  = wiringPiI2CSetup(MOTOR2_ID);
    if (status == -1)
    {
        printf("Motor2 I2C not connected\n");
    }
    status  = wiringPiI2CSetup(MOTOR3_ID);
    if (status == -1)
    {
        printf("Motor3 I2C not connected\n");
    }
    return status;
}

void Motor0Off()
{
    MotorOff(MOTOR0_ID, MOTOR0_OFF_H);
}

void Motor1Off()
{
    MotorOff(MOTOR1_ID, MOTOR1_OFF_H);
}

void Motor2Off()
{
    MotorOff(MOTOR2_ID, MOTOR2_OFF_H);
}

void Motor3Off()
{
    MotorOff(MOTOR3_ID, MOTOR3_OFF_H);
}

void Motor0On(float dutyCyle)
{
    MotorOn(MOTOR0_ID, MOTOR0_ON_L, dutyCyle);
}

void Motor1On(float dutyCyle)
{
    MotorOn(MOTOR1_ID, MOTOR1_ON_L, dutyCyle);
}

void Motor2On(float dutyCyle)
{
    MotorOn(MOTOR2_ID, MOTOR2_ON_L, dutyCyle);
}

void Motor3On(float dutyCyle)
{
    MotorOn(MOTOR3_ID, MOTOR3_ON_L, dutyCyle);
}

void MotorOff(int motorID, int motorOffHAddress)
{
    // per the pwm board documentation, writing a 1 to bit 4 of the _OFF_H
    // register turns the output fully off
    wiringPiI2CWriteReg8(motorID, motorOffHAddress, 0x10);
}

void MotorOn(int motorID, int motorOnLAddress, float dutyCycle)
{
    // per the pwm board documentation. write on value to ON_L
    // then ON_H registers and off value to OFF_L and OFF_H 
    // registers. values are from 0 to 4095
    // no delay time so on value is always 0 (turn on at time 0 of the cycle)
    unsigned short turnOffTime = (unsigned short)(dutyCycle * 4095.0f);
    wiringPiI2CWriteReg16(motorID, motorOnLAddress, 0x0); // this will write 0 to all bits of ON_L and ON_H
    wiringPiI2CWriteReg8(motorID, motorOnLAddress + 2, (turnOffTime & 0xFF)); // write 8 LSBs to OFF_L
    wiringPiI2cWriteReg8(motorID, motorOnLAddress + 3, ((turnOffTime >> 8) & 0xFF)); // write 8 MSBs to OFF_H (only lower 4 bits can be non-zero)
}