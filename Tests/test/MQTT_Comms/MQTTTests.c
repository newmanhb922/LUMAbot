#include "../../../src/MQTT_Comms/MQTTModule.h"

int main()
{
    char * messageToPublish;
    MQTTClient client;
    ConnectToMQTT(&client);
    SubscribeToTopic(&client, "Command");
    SubscribeToTopic(&client, "TargetPosition");
    for (int i = -10; i <= 10; i+= 2)
    {
        sprintf(messageToPublish, "%d, %d", i, i);
        printf("Publishing message: %s\n", messageToPublish);
        PublishMessage(&client, "CurrentPosition", messageToPublish);
        sleep(1);
    }
}