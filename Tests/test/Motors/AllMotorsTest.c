#include "../../../src/GeneralControls/Motors/MotorControl.h"
#include "../../../src/I2C_Module/I2CModule.h"
#include <stdio.h>

int main()
{
    float dutyCycle = 0;
    int direction = 0;
    char * dirStr = "";
    SetupMotors();
    SetupI2C();
    for (int i = 0; i < 10; i++)
    {
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
        printf("Setting motors to move %s at %.2f%% duty cycle.\n", dirStr, dutyCycle);
        SetMotorDir(1, direction);
        SetMotorDir(2, direction);
        SetMotorDir(3, direction);
        SetMotorDir(4, direction);
        SetMotorPWM(1, dutyCycle);
        SetMotorPWM(2, dutyCycle);
        SetMotorPWM(3, dutyCycle);
        SetMotorPWM(4, dutyCycle);
    }
}
