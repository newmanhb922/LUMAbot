#include "MotorControl.h"

void SetupMotors()
{
    int returnVal = wiringPiSetup();
    if (returnVal == 0)
    {
        printf("wiringPiSetup success\n");
    }
    else 
    {
        printf("wiringPiSetup failed\n");
    }
    pinMode(MOTOR_1_DIR, OUTPUT);
    pinMode(MOTOR_2_DIR, OUTPUT);
    pinMode(MOTOR_3_DIR, OUTPUT);
    pinMode(MOTOR_4_DIR, OUTPUT);
}

void SetMotorDir(int motorNum, bool forward)
{
    int motorPin = 0;
    switch (motorNum)
    {
        case 1:
            motorPin = MOTOR_1_DIR;
            break;
            case 2:
            motorPin = MOTOR_2_DIR;
            break;
        case 3:
            motorPin = MOTOR_3_DIR;
            break;
        case 4:
            motorPin = MOTOR_4_DIR;
            break;
        default:
            motorPin = -1;
            break;
    }
    digitalWrite(motorPin, forward);
}
