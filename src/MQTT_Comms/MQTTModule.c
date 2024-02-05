#include "MQTTModule.h"

void ConnectionLost(void * context, char * cause)
{
    // Connection Lost
}

int MessageArrived(void * context, char * topicName, int topicLen, MQTTClient_message * message)
{
    printf("message arrived. Topic: %s, Message: %s\n", topicName, message->payload);
    if (strcmp(topicName, CURRENTPOSITIONTOPIC) == 0)
    {
        // should never receive a message with current position topic
    }
    else if (strcmp(topicName, TARGETPOSITIONTOPIC) == 0)
    {
        // set target position
    }
    else if (strcmp(topicName, COMMANDTOPIC) == 0)
    {
        // execute command
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
        printf("Callbacks set\n");
    }
    return returnCode;
}

int SubsribeToTopic(MQTTClient * client, const char * topicName)
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
    returnCode = MQTTClient_waitForCompletion(*client, deliveryToken, TIMEOUT);
    printf("Message Published: %s, DeliveryToken: %d\n", message, deliveryToken);
    return returnCode;
}