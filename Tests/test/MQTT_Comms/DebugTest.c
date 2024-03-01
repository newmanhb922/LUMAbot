#include "../../../src/MQTT_Comms/MQTTModule.h"
#include <stdio.h>

int main()
{
    char * message = "";
    MQTTClient client;
    for (int i = 0; i < 30; i++)
    {
        printf("Type a debug message to send to the UI.\n");
        scanf("%s", message);
        PublishMessage(&client, DEBUG_TOPIC, message);
    }
}