#include "MotorControl.h"
#include "Controller.h"
#include "Ultrasonic.h"
#include "I2CModule.h"
#include "MQTTModule.h:"

//Objects
MQTTClient client;

//Init Functions
ConnectToMQTT(&client);
SetupI2C();
SetUpMotors();
InitController();
UltrasonicInit();



