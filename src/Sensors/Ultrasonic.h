#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <wiringPi.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../MQTT_Comms/MQTTModule.h"

// these are the wiringPi pin definitions.
// see pinout.xyz/pinout/wiringpi for the corresponding rpi gpio pins
// echo pin can't be wired directly into raspberry pi
// have to use voltage divider circuit to generate 3.3 V from sensors 5 V output
#define SENSOR_1_ECHO		0 // raspberry pi pin 11
#define SENSOR_2_ECHO		1 // raspberry pi pin 12
#define SENSOR_3_ECHO		4 // raspberry pi pin 16
#define SENSOR_4_ECHO       5 // raspberry pi pin 18
#define SENSOR_1_TRIG       6 // raspberry pi pin 22
#define SENSOR_2_TRIG       10 // raspberry pi pin 24
#define SENSOR_3_TRIG       11 // raspberry pi pin 26
#define SENSOR_4_TRIG       31 // raspberry pi pin 28
// #define SENSOR_5_TRIG       26
// #define SENSOR_6_TRIG       27
// #define SENSOR_7_TRIG       28
// #define SENSOR_8_TRIG       29
#define SPEED_OF_SOUND      343.8 // approximate speed of sound in 69.8 degree F air

#define NUM_OF_SENSORS      4

#define CM_PER_IN            2.54f

#define MAX_DISTANCE		16.0f

// distance from sensor to object in inches
extern volatile float sensor1Val;
extern volatile float sensor2Val;
extern volatile float sensor3Val;
extern volatile float sensor4Val;
// volatile float sensor5Val;
// volatile float sensor6Val;
// volatile float sensor7Val;
// volatile float sensor8Val;

/// @brief Initializes pins for ultrasonic sensors
void UltrasonicInit();

/// @brief Reads the ultrasonic sensors
void ReadUltrasonicSensors();
#endif
