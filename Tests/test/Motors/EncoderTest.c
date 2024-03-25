#include "../../../src/GeneralControls/Motors/MotorControl.h"
#include "../../../src/I2C_Module/I2CModule.h"
#include <stdio.h>

extern volatile int encoder1Count;

int main()
{
    int motorNum = 0;
    float dutyCycle = 0;
    int direction = 0;
    char * dirStr = "";
    SetupMotors();
    SetupI2C();

    printf("Initial encoder1Count value: %d\n", encoder1Count);

    printf("Enter motor number.\n");
    scanf("%d", &motorNum);
    printf("Enter duty cycle.\n");
    scanf("%f", &dutyCycle);
    printf("Enter direction (1 for forward, 0 for reverse).\n");
    scanf("%d", &direction);
    if (direction)
    {
        dirStr = "Forward";
    }
    else
    {
        dirStr = "Reverse";
    }
    printf("Setting motor %d to move %s at %.2f%% duty cycle.\n", motorNum, dirStr, dutyCycle);
    SetMotorDir(motorNum, direction);
    SetMotorPWM(motorNum, dutyCycle);

    printf("Current encoder1Count value: %d\n", encoder1Count);
    printf("Enter 1 to turn motor forward, 0 to turn motor in reverse\n");

    for (int i = 0; i < 100; i++)
    {
        direction = getChar();
        if (direction >= 0 && direction <= 1)
        {
            SetMotorDir(motorNum, direction);
        }
        printf("Current encoder1Count value: %d\n", encoder1Count);
        printf("Enter 1 to turn motor forward, 0 to turn motor in reverse\n");
    }
}