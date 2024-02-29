#include "../../../src/Sensors/Ultrasonic.h"
#include <wiringPi.h>
#include <stdio.h>

extern unsigned int sensor1Val;

int main()
{
    printf("Initializing ultrasonic sensors and setting timer to measure every 200 ms.\n");
    UltrasonicInit();
    StartSampling(200000);
    for (int i = 0; i < 10; i++)
    {
        printf("Sensor 1 val: %d. Press enter to see update.\n", sensor1Val);
        int ch = getchar();
    }
}