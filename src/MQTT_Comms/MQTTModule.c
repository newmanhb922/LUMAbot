#include "MQTTModule.h"

int ConnectToMQTT(MQTTClient * client)
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int returnCode = -1;

    // create client object
    if ((returnCode == MQTTClient_create(client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        // error
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    // connect to mqtt server
    if ((returnCode == MQTTClient_connect(*client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        // error
    }
    return returnCode;
}