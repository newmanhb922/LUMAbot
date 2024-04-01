#include "src/GeneralControls/Motors/MotorControl.h"
#include "src/Controller/Controller.h"
#include "src/Sensors/Ultrasonic.h"
#include "src/I2C_Module/I2CModule.h"
#include "src/MQTT_Comms/MQTTModule.h"
#include "src/GeneralControls/Position/Position.h"
#include "src/AutomatedControls/Fsm.h"

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
}




