#include "MotorControl.h"
#include "Controller.h"
#include "Ultrasonic.h"
#include "I2CModule.h"
#include "MQTTModule.h"
#include "Position.h"
#include "Fsm.h"

//Objects
MQTTClient client;

int main()
{
    //Init Functions

    // init mqtt and subscribe to topics
    ConnectToMQTT(&client);
    SubscribeToTopic(&client, CURRENT_POSITION_TOPIC);
    SubscribeToTopic(&client, TARGET_POSITION_TOPIC);
    SubscribeToTopic(&client, COMMAND_TOPIC);

    SetupI2C();
    InitController();
    UltrasonicInit();
    InitPosition();
    StartSamplingData();
    Fsm_Init();

    while(1)
    {
        RunStateFunction();
    }
}




