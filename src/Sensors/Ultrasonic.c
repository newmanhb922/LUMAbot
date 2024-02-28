#include "Ultrasonic.h"

void UltrasonicInit()
{
    wiringPiSetup();
    pinMode(ECHO_PIN, INPUT);
    pinMode(SENSOR_1_TRIG, OUTPUT);
    pinMode(SENSOR_2_TRIG, OUTPUT);
    pinMode(SENSOR_3_TRIG, OUTPUT);
    pinMode(SENSOR_4_TRIG, OUTPUT);
    pinMode(SENSOR_5_TRIG, OUTPUT);
    pinMode(SENSOR_6_TRIG, OUTPUT);
    pinMode(SENSOR_7_TRIG, OUTPUT);
    pinMode(SENSOR_8_TRIG, OUTPUT);
}

void BeginSampling()
{ // don't know how to set up timer and interrupts
    
}