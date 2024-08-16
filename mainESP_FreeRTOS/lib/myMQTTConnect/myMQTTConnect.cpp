#include "myMQTTConnect.h"
#include <Arduino.h>

extern QueueHandle_t qCommandQueue;
// extern HardwareSerial serialScreen(1);

myMQTTConnect* myMQTTConnect::instance = nullptr;

myMQTTConnect::myMQTTConnect() {
    instance = this;
}

void myMQTTConnect::setupMQTT(Client& client) {
    mqttClient.setClient(client);
    mqttClient.setServer(mqtt_server, mqtt_port);
    mqttClient.setCallback(mqttCallbackStatic);
    reconnectMQTT();
}

void myMQTTConnect::mqttCallbackStatic(char* topic, byte* payload, unsigned int length) {
    if (instance) {
        instance->mqttCallback(topic, payload, length);
    }
}

void myMQTTConnect::mqttCallback(char* topic, byte* payload, unsigned int length) {
    String strMessage = "";
    String strTopic = topic;
    for (int i = 0; i < length; i++) {
        strMessage += (char)payload[i];
    }
    // Serial.println("Message arrived [" + String(strTopic) + "] " + strMessage);
    // if (strTopic == topic_subscribe_screen){serialScreen.print("screen1@");}
    // Add received message to a struct
    sCommand sCommand;
    sCommand.strTopic = strTopic;
    sCommand.strMessage = strMessage;
    // Add struct MQTT message to queue
    xQueueSend(qCommandQueue, &sCommand, portMAX_DELAY);
}

void myMQTTConnect::reconnectMQTT() 
{
    while (!mqttClient.connected()) {
        Serial.println("Attempting MQTT connection...");
        String client_id = String(esp32MACAddress);
        if (mqttClient.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("MQTT connected");
            mqttClient.subscribe(topic_subscribe_subOTP);
            mqttClient.subscribe(topic_subscribe_screen);
            mqttClient.subscribe(topic_subscribe_publichStatus);
        } else {
            Serial.println("MQTT connection failed, retrying in 5 seconds");
            delay(5000);
        }
    }
}

void myMQTTConnect::loop() 
{
    if (!mqttClient.connected()) {
        reconnectMQTT();
    }
    mqttClient.loop();
}

void myMQTTConnect::sendMessageToServer(String strTopic, String strMessage)
{
    mqttClient.publish(strTopic.c_str(), strMessage.c_str());
    // addMessageToQueue("Message sent to [" + String(topic_publish) + "] " + strMessageSentToServer);
}