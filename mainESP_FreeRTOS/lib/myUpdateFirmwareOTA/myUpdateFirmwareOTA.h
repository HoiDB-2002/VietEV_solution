#pragma once

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include "myLib.h"

// This class to Update firmware by connecting to a another wifi
class myUpdateFirmwareOTA {
public:
    myUpdateFirmwareOTA();
    void begin();
    void handleClient();

private:
    static void setupOTA();
    static void handleUpdate();
    static void handleUpdateStatus();
    static void handleUpload();
    static void checkLogin();
    
    static WebServer server;

    static const char* loginIndex;
    static const char* serverIndex;
};
