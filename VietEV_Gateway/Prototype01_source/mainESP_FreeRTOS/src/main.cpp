#include <Arduino.h>

#include "myLib.h"

#include "myInternet.h"
myInternet internet;

#include "myMQTTConnect.h"
myMQTTConnect mqttConnect;

#include "myUpdateFirmwareOTA.h"
myUpdateFirmwareOTA updateFirmwareOTA;

#include "myKeypad.h"
myKeypad keypad;

#define esp32_CORE0 0
#define esp32_CORE1 1

int nState = stateDefault;
sPowerInfor sPowerInfor1;
int nStateGetPowerInfor = Off;
int nMode = modeUser;

// Serial port send command to screen
HardwareSerial serialScreen(1);
// Serial port received data from power meter
#include <PZEM004Tv30.h>
HardwareSerial serialPowerMeter(2);
PZEM004Tv30 pzem(serialPowerMeter, RX2, TX2);

// MQTT command queue
QueueHandle_t qCommandQueue;
// Serial message queue
QueueHandle_t qSerialMessageQueue;

// Manage Internet connection
void taskInternet(void *pvParameters);
// Manage MQTT connection
void taskMQTT(void *pvParameters);
// Manage all main program state
void taskManageProgram(void *pvParameters);
// Manage all message want to print on Serial screen
void taskPrintSerial(void *pvParameters);
// Manage OTA firmware updates
void taskUpdateFirmwareOTA(void *pvParameters);
// Get power information
void taskGetPowerInfor(void *pvParameters);
// Keypad with module I2C PCF8574
void taskKeypad(void *pvParameters);

// Add message want to print on Serial screen to queue
void funcSerialPrintln(const String &strSerialPrintln);
// Combo send message to serial monitor, screen, MQTTX
void funcSendComboMessage(const String &strMessage);
// Split message to small string
sMessage funcSplitMessage(String strMessage);

// ************************************** Set up and Initialization *****************************************************
void setup()
{
  nState = stateInitProgram;
  // Set up debug Serial
  Serial.begin(115200);
  serialScreen.begin(9600, SERIAL_8N1, RX1, TX1);
  serialPowerMeter.begin(9600, SERIAL_8N1, RX2, TX2);
  serialScreen.print("screen0@");

  Serial.println("InitProgram|Serial begined");

  // Set up GPIO device
  pinMode(relayPin, OUTPUT);

  // Set up command queue
  qCommandQueue = xQueueCreate(10, sizeof(sCommand));
  // Set up message queue to print on serial
  qSerialMessageQueue = xQueueCreate(10, sizeof(String));

  // Kết nối WiFi
  Serial.println("InitProgram|Wifi connecting to " + internet.getSSID());
  // serialScreen.print("InitProgram|Wifi connecting to " + internet.getSSID());
  bool connected = false;
  connected = internet.connectWifi();
  // Hoặc kết nối Ethernet
  // connected = internet.connectEthernet();

  if (connected)
  {
    Serial.println("InitProgram|Wifi connected");
    Serial.println("InitProgram|Wifi IP Address: " + internet.getIPAdress());
    mqttConnect.setupMQTT(internet.getClient());
  }

  // ----------------------------- Declare FreeRTOS task ---------------------------------------------
  xTaskCreatePinnedToCore(
      taskInternet,
      "taskInternet",
      2048,
      NULL,
      2,
      NULL,
      esp32_CORE0);

  xTaskCreatePinnedToCore(
      taskMQTT,
      "taskMQTT",
      2048,
      NULL,
      1,
      NULL,
      esp32_CORE0);

  xTaskCreatePinnedToCore(
      taskManageProgram,
      "taskManageProgram",
      2048,
      NULL,
      4,
      NULL,
      esp32_CORE1);

  xTaskCreatePinnedToCore(
      taskPrintSerial,
      "taskPrintSerial",
      2048,
      NULL,
      3,
      NULL,
      esp32_CORE1);

  xTaskCreatePinnedToCore(
      taskUpdateFirmwareOTA,
      "taskUpdateFirmwareOTA",
      8192,
      NULL,
      0,
      NULL,
      esp32_CORE0);

  xTaskCreatePinnedToCore(
      taskGetPowerInfor,
      "taskGetPowerInfor",
      2048,
      NULL,
      2,
      NULL,
      esp32_CORE1);

  xTaskCreatePinnedToCore(
      taskKeypad,
      "taskKeypad",
      2048,
      NULL,
      1,
      NULL,
      esp32_CORE1);
  // ----------------------------------------------------------------------------------------------
}

void loop() {}
// *********************************************************************************************************

void taskInternet(void *pvParameters)
{
  Serial.println("taskInternet set up core 0");
  for (;;)
  {
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void taskMQTT(void *pvParameters)
{
  Serial.println("taskMQTT set up core 0");
  for (;;)
  {
    mqttConnect.loop();

    // gửi message lên server
    static unsigned long ulLastMsgTime = 0;
    if (millis() - ulLastMsgTime > 15000)
    {
      ulLastMsgTime = millis();
      mqttConnect.sendMessageToServer(topic_publish, strMessageSentToServer);
      funcSerialPrintln("Message sent [" + String(topic_publish) + "] " + String(strMessageSentToServer));
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void taskManageProgram(void *pvParameters)
{
  Serial.println("taskManageProgram set up core 1");
  sCommand sCommand;
  String strTopic;
  String strMessage;

  // State ready to charge EV
  nState = stateReadyToChargeEV;

  for (;;)
  {
    if (xQueueReceive(qCommandQueue, &sCommand, portMAX_DELAY) == pdPASS)
    {
      // Tách phần topic và command
      strTopic = sCommand.strTopic;
      strMessage = sCommand.strMessage;

      sMessage myMessage = funcSplitMessage(strMessage);
      if (myMessage.parts[pDeviceName] == String(deviceName))
      {
        funcSerialPrintln("[" + strTopic + "] " + strMessage);
        if (nState == stateReadyToChargeEV)
        {
          if (strTopic == topic_subscribe_publichStatus)
          {
            if (myMessage.parts[1] == "relayOn")
            {
              funcSerialPrintln("Relay is on");
              digitalWrite(relayPin, HIGH);
              serialScreen.print("screen2@");
              pzem.resetEnergy();
              nStateGetPowerInfor = On;
            }
            else if (myMessage.parts[1] == "relayOff")
            {
              funcSerialPrintln("Relay is off");
              nStateGetPowerInfor = Off;
              digitalWrite(relayPin, LOW);
              serialScreen.print("screen3@");
            }
            else
            {
              funcSendComboMessage(String(deviceName) + "|" + "Command not found");
            }
          }
          else if (strTopic == topic_subscribe_screen)
          {
            if (myMessage.parts[1] == "screen1@")
            {
              // serialScreen.print("screen1@");
              digitalWrite(relayPin, LOW);
              nStateGetPowerInfor = Off;
            }
            else if (myMessage.parts[1] == "screen2@")
            {
              serialScreen.print("screen2@");
              digitalWrite(relayPin, HIGH);
              nStateGetPowerInfor = On;
            }
            else if (myMessage.parts[1] == "screen3@")
            {
              serialScreen.print("screen3@");
              digitalWrite(relayPin, LOW);
              nStateGetPowerInfor = Off;
            }
            else
            {
              nStateGetPowerInfor = Off;
              serialScreen.print("screen0@");
            }
          }
          else if (strTopic == topic_subscribe_subOTP)
          {
            nStateGetPowerInfor = Off;
            serialScreen.print(myMessage.parts[1]);
            digitalWrite(relayPin, LOW);
          }
          else
          {
            funcSendComboMessage(String(deviceName) + "|" + "Topic not found");
          }
        }
      }
    }
  }
}

void taskPrintSerial(void *pvParameters)
{
  Serial.println("taskPrintSerial set up core 1");
  String strSerialPrintln;
  for (;;)
  {
    if (xQueueReceive(qSerialMessageQueue, &strSerialPrintln, portMAX_DELAY) == pdPASS)
    {
      Serial.println(strSerialPrintln);
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void taskUpdateFirmwareOTA(void *pvParameters)
{
  updateFirmwareOTA.begin();

  for (;;)
  {
    updateFirmwareOTA.handleClient();
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}

void taskGetPowerInfor(void *pvParameters)
{

  for (;;)
  {
    // funcSerialPrintln(String(nStateGetPowerInfor == On));
    if (nStateGetPowerInfor == On)
    {
      sPowerInfor1.fVoltage = pzem.voltage();
      sPowerInfor1.fCurrent = pzem.current();
      sPowerInfor1.fPower = pzem.power();
      sPowerInfor1.fEnergy = pzem.energy();
      sPowerInfor1.fFrequency = pzem.frequency();

      String strMessage = "PowerInfor |";
      if (isnan(sPowerInfor1.fVoltage))
      {
        strMessage += "Vol: Error| ";
      }
      else
      {
        strMessage += "Vol: " + String(sPowerInfor1.fVoltage, 2) + "V| ";
      }

      if (isnan(sPowerInfor1.fCurrent))
      {
        strMessage += "Cur: Error| ";
      }
      else
      {
        strMessage += "Cur: " + String(sPowerInfor1.fCurrent, 2) + "A| ";
      }

      if (isnan(sPowerInfor1.fPower))
      {
        strMessage += "Pow: Error| ";
      }
      else
      {
        strMessage += "Pow: " + String(sPowerInfor1.fPower, 2) + "W| ";
      }

      if (isnan(sPowerInfor1.fEnergy))
      {
        strMessage += "Ene: Error| ";
      }
      else
      {
        strMessage += "Ene: " + String(sPowerInfor1.fEnergy, 2) + "Wh| ";
      }

      if (isnan(sPowerInfor1.fFrequency))
      {
        strMessage += "Fre: Error| ";
      }
      else
      {
        strMessage += "Fre: " + String(sPowerInfor1.fFrequency, 2) + "HZ| ";
      }

      strMessage += "@";

      // funcSerialPrintln(message);
      // mqttConnect.sendMessageToServer(topic_publish, message);
      // serialScreen.print(message);
      // serialScreen.write((uint8_t*)&sPowerInfor1, sizeof(sPowerInfor));
      funcSendComboMessage(strMessage);
    }

    vTaskDelay(pdMS_TO_TICKS(10000)); // Read data every 2 seconds
  }
}

void taskKeypad(void *pvParameters)
{
  keypad.initKeypad();
  int nLastKey = btNull; // To store the last key pressed

  for (;;)
  {
    int nCode = keypad.scanMatrix();

    if (nCode != btNull && nCode != nLastKey)
    {
      funcSerialPrintln("Button [" + String(nCode) + "] is pressed");

      switch (nCode)
      {
        case btOne:
        {
          funcSendComboMessage("screen1@");
          break;
        }
        case btTwo:
        {
          funcSendComboMessage("screen2@");
          break;
        }
        case btThree:
        {
          funcSendComboMessage("screen3@");
          break;
        }
        default:
        {
          funcSendComboMessage("screen0@");
          break;
        }
      }

      nLastKey = nCode;
    }
    else if (nCode == btNull)
    {
      nLastKey = btNull; // Reset nLastKey when no key is pressed
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void funcSerialPrintln(const String &strSerialPrintln)
{
  if (qSerialMessageQueue != NULL)
  {
    xQueueSend(qSerialMessageQueue, &strSerialPrintln, portMAX_DELAY);
  }
}

void funcSendComboMessage(const String &strMessage)
{
  funcSerialPrintln(strMessage);
  serialScreen.print(strMessage);
  mqttConnect.sendMessageToServer(topic_publish, strMessage);
}

sMessage funcSplitMessage(String strMessage)
{
  sMessage result;

  int startIndex = 0;
  int endIndex = 0;

  // Split middle string by |
  while ((endIndex = strMessage.indexOf('|', startIndex)) != -1)
  {
    result.parts.push_back(strMessage.substring(startIndex, endIndex));
    startIndex = endIndex + 1;
  }

  // Add final string after character |
  result.parts.push_back(strMessage.substring(startIndex));

  return result;
}