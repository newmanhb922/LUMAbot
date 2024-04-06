#include "MQTTModule.h"

MQTTAsync * mqttClient;

extern float curPositionX;
extern float curPositionY;
extern float targetPositionX;
extern float targetPositionY;
extern bool eStopPressed;
extern bool hasBeenZeroed;
extern bool goPressed;

bool connected;

void ConnectionLost(void * context, char * cause)
{
    // Connection Lost
}

int MessageArrived(void * context, char * topicName, int topicLen, MQTTAsync_message * message)
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
        char xCoord[10];
        char yCoord[10];
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
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}

void OnConnect(void* context, MQTTAsync_successData* response)
{
    connected = true; // signal that we successfully connected
}

int ConnectToMQTT(MQTTAsync * client)
{
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    int returnCode = -1;
    connected = false;
    // create client object
    if ((returnCode = MQTTAsync_create(client, ADDRESS, CLIENTID, MQTTASYNC_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
    {
        // error
        printf("error creating client\n");
    }
    else
    {
        printf("Client created\n");
    }
    if ((returnCode = MQTTAsync_setCallbacks(*client, NULL, ConnectionLost, MessageArrived, NULL)) != MQTTASYNC_SUCCESS)
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
    conn_opts.onSuccess = OnConnect;
    // connect to mqtt server
    if ((returnCode = MQTTAsync_connect(*client, &conn_opts)) != MQTTASYNC_SUCCESS)
    {
        // error
        printf("error connecting\n");
    }
    else
    {
        while (!connected); // wait until connected
        printf("Connected\n");
        mqttClient = client;
    }
    return returnCode;
}

int SubscribeToTopic(MQTTAsync * client, const char * topicName)
{
    int returnCode = -1;
    if ((returnCode = MQTTAsync_subscribe(*client, topicName, QOS, NULL)) != MQTTASYNC_SUCCESS)
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

int PublishMessage(MQTTAsync * client, const char * topicName, char * message)
{
    MQTTAsync_message toPublish = MQTTAsync_message_initializer;
    int returnCode = -1;

    toPublish.payload = message;
    toPublish.payloadlen = strlen(message);
    toPublish.qos = QOS;
    toPublish.retained = 0;

    if ((returnCode = MQTTAsync_sendMessage(*client, topicName, &toPublish, NULL)) != MQTTASYNC_SUCCESS)
    {
        // error
        printf("error sending message\n");
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

void SendCurPositionToUI()
{
    char helperStr[100];
    sprintf(helperStr, "%.2f, %.2f", curPositionX, curPositionY);
    PublishMessage(mqttClient, CURRENT_POSITION_TOPIC, helperStr);
}
