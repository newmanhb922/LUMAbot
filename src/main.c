#include "GeneralControls/Motors/MotorControl.h"
#include "Controller/Controller.h"
#include "Sensors/Ultrasonic.h"
#include "I2C_Module/I2CModule.h"
#include "MQTT_Comms/MQTTModule.h"
#include "GeneralControls/Position/Position.h"
#include "AutomatedControls/Fsm.h"

//Objects
MQTTClient client;
//MQTTAsync client;
int main()
{
    //Init Functions

    // init mqtt and subscribe to topics
    ConnectToMQTT(&client);
//    SubscribeToTopic(&client, CURRENT_POSITION_TOPIC);
    SubscribeToTopic(&client, TARGET_POSITION_TOPIC);
    SubscribeToTopic(&client, COMMAND_TOPIC);

    SetupI2C();
    InitController();
    UltrasonicInit();
    InitPosition();
    SetupMotors();
    StartSamplingData();
    Fsm_Init();

    while(1)
    {
        RunStateFunction();
    }
}




