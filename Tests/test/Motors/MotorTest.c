#include "../../../src/General Controls/Motors/MotorControl.h"
#include "../../../src/I2C_Module/I2CModule.h"
#include <stdio.h>

int main()
{
    int motorNum = 0;
    float dutyCycle = 0;
    int direction = 0;
    char * dirStr = "";
    SetupMotors();
    SetupI2C();
    for (int i = 0; i < 10; i++)
    {
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
        printf("Setting motor %d to move %s at %f%% duty cycle.\n", motorNum, dirStr, dutyCycle);
    }
}