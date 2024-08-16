#include "Lib.h"
#include <SoftwareSerial.h>
#include "DisplayScreen.h"

SoftwareSerial mySerial(12, 13);  // RX, TX
DisplayScreen ds;

// Biến kiểm tra đã vẽ hay chưa
int nDrawn = drawFasle;
int nState = stWelcome;
String strQRCode = "324689";

// Get data Power Information
float getPowerInformation(String strData, String strStartChar, String strEndChar);

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

  // Khởi tạo LCD
  ds.initLCD();
}

void loop() {
  // Nhận dữ liệu qua cổng soft Serial (ESP32)
  if (mySerial.available() > 0) {
    // Đọc chuỗi truyền xuống đến kí tự '@'
    String str = mySerial.readStringUntil('@');
    Serial.println(str);

    if (str == "-1") {
      nState = stDefault;
      nDrawn = drawFasle;
    }
    if (str == "screen0") {
      nState = stWelcome;
      nDrawn = drawFasle;
    }
    if (str == "screen1") {
      nState = stDisplayOTP;
      nDrawn = drawFasle;
    }
    if (str == "screen2") {
      nState = stChargingEV;
      previousPower = 0;
      nDrawn = drawFasle;
    }
    if (str == "screen3") {
      nState = stChargingEVCompleted;
      nDrawn = drawFasle;
    }
    if (str.substring(0, 3) == "OTP") {
      nState = stDisplayOTP;
      nDrawn = drawFasle;
      strQRCode = str.substring(3, 9);
    }
    if (nDrawn == drawInfor) {
      sPowerInfor sPowerInfor2;
      sPowerInfor2.fVoltage = getPowerInformation(str, "Vol: ", "V");
      sPowerInfor2.fCurrent = getPowerInformation(str, "Cur: ", "A");
      sPowerInfor2.fPower = getPowerInformation(str, "Pow: ", "W");
      sPowerInfor2.fEnergy = getPowerInformation(str, "Ene: ", "Wh");
      sPowerInfor2.fFrequency = getPowerInformation(str, "Fre: ", "HZ");
      // Serial.println(String(sPowerInfor2.fVoltage) + "V");
      // Serial.println(String(sPowerInfor2.fCurrent) + "A");
      // Serial.println(String(sPowerInfor2.fPower) + "W");
      // Serial.println(String(sPowerInfor2.fEnergy) + "Wh");
      // Serial.println(String(sPowerInfor2.fFrequency) + "HZ");
      ds.drawDataUpdate(sPowerInfor2);
    }
    // if (str == "324689") {nState=1; nDrawn=false;}
  }

  // Nhận dữ liệu qua cổng hard Serial (màn hình Serial/ D0 D1)
  if (Serial.available() > 0) {
    // Đọc chuỗi truyền xuống đến kí tự '@'
    String str1 = Serial.readStringUntil('@');
    // mySerial.print(str1);

    if (str1 == "-1") {
      nState = stDefault;
      nDrawn = drawFasle;
    }
    if (str1 == "screen0") {
      nState = stWelcome;
      nDrawn = drawFasle;
    }
    if (str1 == "screen1") {
      nState = stDisplayOTP;
      nDrawn = drawFasle;
    }
    if (str1 == "screen2") {
      nState = stChargingEV;
      nDrawn = drawFasle;
    }
    if (str1 == "screen3") {
      nState = stChargingEVCompleted;
      nDrawn = drawFasle;
    }
  }

  // Vẽ màn hình hiển thị
  if (nDrawn == drawFasle) {
    if (nState == stDefault) ds.displayScreenTest();
    if (nState == stWelcome) ds.displayScreen_Welcome();
    if (nState == stDisplayOTP) ds.displayScreen_ScanOTP();
    if (nState==stChargingEV) ds.displayScreen_ChargingVehicle();
    if (nState == stChargingInfor) ds.displayScreenTest();
    if (nState == stChargingEVCompleted) ds.displayScreen_CompletedCharging();
    nDrawn = drawTrue;
  }
  if (nState == stChargingEV) nDrawn = drawInfor;


  // Serial.println(nState);
  // if (nDrawn == drawInfor) {

  //   Serial.println("ok");
  //   if (mySerial.available() >= sizeof(sPowerInfor)) {
  //     sPowerInfor sPowerInfor1;
  //     mySerial.readBytes((char*)&sPowerInfor1, sizeof(sPowerInfor));
  //     Serial.println(sPowerInfor1.fVoltage);
  //     ds.drawPowerUpdate(sPowerInfor1.fVoltage);
  //   }
  // }
}

float getPowerInformation(String strData, String strStartChar, String strEndChar) {
  int startIndex = strData.indexOf(strStartChar) + strStartChar.length();
  int endIndex = strData.indexOf(strEndChar, startIndex);
  String valueStrData = strData.substring(startIndex, endIndex);
  return valueStrData.toFloat();
}
