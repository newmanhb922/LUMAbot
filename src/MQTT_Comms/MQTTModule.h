#include "paho.mqtt.c/src/MQTTClient.h"
#include <string.h>

#define ADDRESS     "localhost"
#define CLIENTID    "RaspPi"
#define QOS         1
#define TIMEOUT     10000L

const char * CurrentPositionTopic = "CurrentPosition";
const char * TargetPositionTopic = "TargetPosition";
const char * CommandTopic = "Command";

/// @brief Connects to mqtt server and returns a return code.
/// @param client pointer to an MQTTClient object 
/// @return returns a code specifying whether the connection succeeded.
int ConnectToMQTT(MQTTClient * client);

/// @brief Subscribes to topic specified by topicName
/// @param client pointer to MQTTClient object
/// @param topicName topic name to subscribe to
/// @return returns a code specifying success or failure
int SubscribeToTopic(MQTTClient * client, const char topicName);

/// @brief Publishes a message
/// @param client pointer to MQTTClient object
/// @param topicName topic name to send message to
/// @param message message contents
/// @return returns a code specifying success or failure
int PublishMessage(MQTTClient * client, const char topicName, const char message);