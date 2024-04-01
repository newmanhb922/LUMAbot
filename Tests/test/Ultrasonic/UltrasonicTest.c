#include "../../../src/Sensors/Ultrasonic.h"
//#include "../../../src/MQTT_Comms/MQTTModule.h"
#include <wiringPi.h>
#include <stdio.h>

extern volatile float sensor1Val;

int main()
{
    printf("Initializing ultrasonic sensors and setting timer to measure every 200 ms.\n");
    UltrasonicInit();
    StartSampling(200000);
    for (int i = 0; i < 10; i++)
    {
        printf("Sensor 1 val: %.2f. Press enter to see update.\n", sensor1Val);
        int ch = getchar();
    }
}
