#include "I2CModule.h"

/// @brief turns the specified motor off
/// @param motorOffHAddress address of the OFF_H register for this motor
void MotorOff(int motorOffHAddress);

/// @brief sets speed of a specified motor
/// @param motorOnLAddress address of the ON_L register for this motor
/// @param dutyCycle duty cycle as a percentage
void MotorSetPWM(int motorOnLAddress, float dutyCycle);

int SetupI2C()
{
    int status = 0;

    status  = wiringPiI2CSetup(PWM_BOARD_ID);
    if (status == -1)
    {
        printf("I2C not connected\n");
    }
    // set prescale register value to 0x03. This is minimum value and results in 
    // max frequency of 1526 Hz
    wiringPiI2CWriteReg8(PWM_BOARD_ID, PRE_SCALE_REG, 0x03);
    // enable auto increment and take out of sleep
    wiringPiI2CWriteReg8(PWM_BOARD_ID, MODE1_REG, (1 << AUTO_INCR_BIT) | (0 << SLEEP_BIT));
    return status;
}

void TurnMotorOff(int motorNum)
{
    switch (motorNum)
    {
        case 1:
            Motor1Off();
            break;
        case 2:
            Motor2Off();
            break;
        case 3:
            Motor3Off();
            break;
        case 4:
            Motor4Off();
            break;
    }
}

void SetMotorPWM(int motorNum, float dutyCycle)
{
    switch (motorNum)
    {
        case 1:
            Motor1SetPWM(dutyCycle);
            break;
        case 2:
            Motor2SetPWM(dutyCycle);
            break;
        case 3:
            Motor3SetPWM(dutyCycle);
            break;
        case 4:
            Motor4SetPWM(dutyCycle);
            break;
    }
}

void Motor1Off()
{
    MotorOff(MOTOR1_OFF_H);
}

void Motor2Off()
{
    MotorOff(MOTOR2_OFF_H);
}

void Motor3Off()
{
    MotorOff(MOTOR3_OFF_H);
}

void Motor4Off()
{
    MotorOff(MOTOR4_OFF_H);
}

void Motor1SetPWM(float dutyCyle)
{
    MotorSetPWM(MOTOR1_ON_L, dutyCyle);
}

void Motor2SetPWM(float dutyCyle)
{
    MotorSetPWM(MOTOR2_ON_L, dutyCyle);
}

void Motor3SetPWM(float dutyCyle)
{
    MotorSetPWM(MOTOR3_ON_L, dutyCyle);
}

void Motor4SetPWM(float dutyCyle)
{
    MotorSetPWM(MOTOR4_ON_L, dutyCyle);
}

void MotorOff(int motorOffHAddress)
{
    // per the pwm board documentation, writing a 1 to bit 4 of the _OFF_H
    // register turns the output fully off
    wiringPiI2CWriteReg8(PWM_BOARD_ID, motorOffHAddress, 0x10);
}

void MotorSetPWM(int motorOnLAddress, float dutyCycle)
{
    // per the pwm board documentation. write on value to ON_L
    // then ON_H registers and off value to OFF_L and OFF_H 
    // registers. values are from 0 to 4095
    // no delay time so on value is always 0 (turn on at time 0 of the cycle)
    unsigned short turnOffTime = (unsigned short)(dutyCycle * 4095.0f);
    wiringPiI2CWriteReg16(PWM_BOARD_ID, motorOnLAddress, 0x0); // this will write 0 to all bits of ON_L and ON_H
    wiringPiI2CWriteReg8(PWM_BOARD_ID, motorOnLAddress + 2, (turnOffTime & 0xFF)); // write 8 LSBs to OFF_L
    wiringPiI2CWriteReg8(PWM_BOARD_ID, motorOnLAddress + 3, ((turnOffTime >> 8) & 0xFF)); // write 8 MSBs to OFF_H (only lower 4 bits can be non-zero)
}
