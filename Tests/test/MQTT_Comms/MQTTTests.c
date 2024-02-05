#include "../../../src/MQTT_Comms/MQTTModule.h"
#include <stdio.h>

void PrintReturnCode(int code);

int main()
{
    char messageToPublish[10];
    MQTTClient client;
    PrintReturnCode(ConnectToMQTT(&client));
    PrintReturnCode(SubscribeToTopic(&client, COMMANDTOPIC));
    PrintReturnCode(SubscribeToTopic(&client, TARGETPOSITIONTOPIC));
    for (int i = 0; i <= 10; i++)
    {
        sprintf(messageToPublish, "%d, %d", i, i);
        printf("Publishing message: %s\n", messageToPublish);
        PrintReturnCode(PublishMessage(&client, CURRENTPOSITIONTOPIC, messageToPublish));
        int ch = getchar();
    }
}

void PrintReturnCode(int code)
{
    printf("Return Code: %d\n", code);
}
