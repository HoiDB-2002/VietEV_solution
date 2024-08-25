#include <Arduino.h>

#include "myLib.h"
#include <myDisplayScreen.h>
myDisplayScreen ds;

HardwareSerial mySerial(1);

int nDrawn = drawFasle;
int nState = stWelcome;
String strQRCode = "324689";

void setup(void)
{
    Serial.begin(115200);
    // while (!Serial)
    // {
    //     delay(10);
    // }
    Serial.println("Serial begin");
    // mySerial.begin(9600, SERIAL_8N1, RX1, TX1);
    // while (!mySerial)
    // {
    //     delay(10);
    // }
    // Serial.println("mySerial begin");

    ds.initLCD();
    ds.displayScreen_ScanOTP();
    ds.displayScreen_Test();
}

void loop()
{
    if (Serial.available() > 0)
    {
        String str = Serial.readStringUntil('@');
        mySerial.print(str);
    }

    if (mySerial.available() > 0)
    {
        String str = mySerial.readStringUntil('@');
        Serial.print(str);
    }
}
