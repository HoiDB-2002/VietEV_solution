#pragma once

#include <PubSubClient.h>
#include "myLib.h"
class myMQTTConnect {
public:
    myMQTTConnect();
    void setupMQTT(Client& client);
    void reconnectMQTT();
    void loop();
    void sendMessageToServer(String strTopic, String strMessage);
    static void mqttCallbackStatic(char* topic, byte* payload, unsigned int length);

private:
    void mqttCallback(char* topic, byte* payload, unsigned int length);

    PubSubClient mqttClient;
    const char* mqtt_server = "broker.emqx.io";
    const char* mqtt_username = "testServerU";
    const char* mqtt_password = "testServerP";
    const int mqtt_port = 1883;

    static myMQTTConnect* instance;
};
