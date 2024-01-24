#include "paho.mqtt.c\src\MQTTClient.h"
#include <string.h>

#define ADDRESS     "localhost"
#define CLIENTID    "RaspPi"
#define QOS         1
#define TIMEOUT     10000L

/// @brief Connects to mqtt server and returns a return code.
/// @param client pointer to an MQTTClient object 
/// @return returns a code specifying whether the connection succeeded.
int ConnectToMQTT(MQTTClient * client);

int SubscribeToTopic(MQTTClient * client, const char topicName);

int PublishMessage(MQTTClient * client, const char topicName, const char message);