#include "MQTTModule.h"

MQTTClient * mqttClient;

extern float curPositionX;
extern float curPositionY;
extern float targetPositionX;
extern float targetPositionY;
extern bool eStopPressed;
extern bool hasBeenZeroed;
extern bool goPressed;

void ConnectionLost(void * context, char * cause)
{
    // Connection Lost
}

int MessageArrived(void * context, char * topicName, int topicLen, MQTTClient_message * message)
{
    printf("message arrived. Topic: %s, Message: %s\n", topicName, message->payload);
    char * receivedMsg = message->payload;

    if (strcmp(topicName, CURRENT_POSITION_TOPIC) == 0)
    { 
        // should never receive a message with current position
        Debug ("Error, received current position in Raspberry Pi.\n");
    }
    else if (strcmp(topicName, TARGET_POSITION_TOPIC) == 0)
    {
        // set target position format is (x,y) but x or y could be two digits and negative
        char * leftParenth = strchr(receivedMsg, '(');
        char * comma = strchr(receivedMsg, ',');
        char * rightParenth = strchr(receivedMsg, ')');
        leftParenth++;
        char * xCoord;
        char * yCoord;
        strncpy(xCoord, leftParenth, comma - leftParenth);
        comma++;
        strncpy(yCoord, comma, rightParenth - comma);
        targetPositionX = strtof(xCoord, NULL);
        targetPositionY = strtof(yCoord, NULL);
        goPressed = true;
    }
    else if (strcmp(topicName, COMMAND_TOPIC) == 0)
    {
        // execute command
        if (strcmp(receivedMsg, ESTOP_COMMAND) == 0)
        {
            Debug("EStop pressed on UI, Shutting down...\n");
            eStopPressed = true;
            // estop pressed, shut down
        }
        else if (strcmp(receivedMsg, ESTOP_RESET_COMMAND) == 0)
        {
            Debug("EStop pressed again on UI, good to move again.\n");
            // e stop pressed again, good to move again
            eStopPressed = false;
        }
        else if (strcmp(receivedMsg, ZERO_COMMAND) == 0)
        {
            Debug ("Zeroed from UI, setting current position to (0,0).\n");
            curPositionX = 0;
            curPositionY = 0;
            hasBeenZeroed = true;
        }
    }
    else if (strcmp(topicName, DEBUG_TOPIC) == 0)
    {
        // should never receive a debug message
    }
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void DeliveryComplete(void * context, MQTTClient_deliveryToken token)
{
    // Delivery Complete
}

int ConnectToMQTT(MQTTClient * client)
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int returnCode = -1;

    // create client object
    if ((returnCode = MQTTClient_create(client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        // error
        printf("error creating client\n");
    }
    else
    {
        printf("Client created\n");
    }
    if ((returnCode = MQTTClient_setCallbacks(*client, NULL, ConnectionLost, MessageArrived, DeliveryComplete)) != MQTTCLIENT_SUCCESS)
    {
        // error
        printf("error setting callbacks\n");
    }
    else
    {
        printf("Callbacks set\n");
    }
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    // connect to mqtt server
    if ((returnCode = MQTTClient_connect(*client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        // error
        printf("error connecting\n");
    }
    else
    {
        printf("Connected\n");
        mqttClient = client;
    }
    return returnCode;
}

int SubscribeToTopic(MQTTClient * client, const char * topicName)
{
    int returnCode = -1;
    if ((returnCode = MQTTClient_subscribe(*client, topicName, QOS)) != MQTTCLIENT_SUCCESS)
    {
        // error
        printf("Error subscribing.\n");
    }
    else
    {
        printf("Subscribed to topic: %s\n", topicName);
    }
    return returnCode;
}

int PublishMessage(MQTTClient * client, const char * topicName, char * message)
{
    MQTTClient_message toPublish = MQTTClient_message_initializer;
    MQTTClient_deliveryToken deliveryToken;
    int returnCode = -1;

    toPublish.payload = message;
    toPublish.payloadlen = strlen(message);
    toPublish.qos = QOS;
    toPublish.retained = 0;

    if ((returnCode = MQTTClient_publishMessage(*client, topicName, &toPublish, &deliveryToken)) != MQTTCLIENT_SUCCESS)
    {
        // error
        printf("error publishing message\n");
    }
 //   returnCode = MQTTClient_waitForCompletion(*client, deliveryToken, TIMEOUT);
//    printf("Message Published: %s, DeliveryToken: %d\n", message, deliveryToken);
    return returnCode;
}

int Debug(char * message)
{
    if (mqttClient != NULL)
    {
        PublishMessage(mqttClient, DEBUG_TOPIC, message);
	return 1;
    }
    return -1;
}
