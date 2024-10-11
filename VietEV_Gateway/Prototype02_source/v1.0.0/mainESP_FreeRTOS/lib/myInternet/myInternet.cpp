#include "myInternet.h"

myInternet::myInternet() : client(nullptr) {}

String myInternet::getSSID()
{
  return ssid;
}

String myInternet::getIPAdress()
{
  return WiFi.localIP().toString();
}

bool myInternet::connectWifi()
{
  delay(10);
  // Serial.println("Connecting to " + String(ssid));

  WiFi.begin(ssid.c_str(), password.c_str());

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: " + WiFi.localIP().toString());

  client = &wifiClient; // Assign WiFi client to generic client pointer
  return true;
}

bool myInternet::connectEthernet()
{
    // Initialize Ethernet here, and check for connection
    // Assuming you have setup Ethernet with proper configuration
    byte mac[6];
    macCharArrayToBytes(ETHERNET_MAC, mac);
    Ethernet.init(ETHERNET_CS_PIN);
    // ethernetWizReset(ETHERNET_RESET_PIN);
    Ethernet.begin(mac);
    while (Ethernet.linkStatus() != LinkON)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("Ethernet connected");
    Serial.println("IP address: " + Ethernet.localIP().toString());

    client = &ethernetClient; // Assign Ethernet client to generic client pointer
    return true;
}

void myInternet::macCharArrayToBytes(const char* str, byte* bytes) {
  for (int i = 0; i < 6; i++) {
    bytes[i] = strtoul(str, NULL, 16);
    str = strchr(str, ':');
    if (str == NULL || *str == '\0') {
      break;
    }
    str++;
  }
}

void myInternet::ethernetWizReset(const uint8_t resetPin) {
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH);
  delay(250);
  digitalWrite(resetPin, LOW);
  delay(50);
  digitalWrite(resetPin, HIGH);
  delay(350);
}

Client &myInternet::getClient()
{
    if (client == nullptr) {
        Serial.println("Error: Client is null!");
    }
    return *client;
}
