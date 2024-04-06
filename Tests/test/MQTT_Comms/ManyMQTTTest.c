#include "../../../src/MQTT_Comms/MQTTModule.h"
#include <stdio.h>

int main()
{
    char messageToPublish[10];
    MQTTClient client;
    ConnectToMQTT(&client);
    for (int i = 0; i <= 100; i++)
    {
        sprintf(messageToPublish, "%d, %d", i, i);
        printf("Publishing message: %s\n", messageToPublish);
        PublishMessage(&client, CURRENT_POSITION_TOPIC, messageToPublish);
        //int ch = getchar();
    }
}