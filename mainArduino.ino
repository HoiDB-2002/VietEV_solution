#include "Lib.h"
#include <SoftwareSerial.h>
#include "DisplayScreen.h"

SoftwareSerial mySerial(12, 13); // RX, TX
DisplayScreen ds;

// Biến kiểm tra đã vẽ hay chưa
bool drawn = false;
int view = 1;
String strQRCode = "324689";

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  // Khởi tạo LCD
  ds.initLCD();

}

void loop() {
  // Nhận dữ liệu qua cổng soft Serial (ESP32) 
  if (mySerial.available() > 0) 
  {
    // Đọc chuỗi truyền xuống đến kí tự '@'
    String str = mySerial.readStringUntil('@');

    if (str == "screen1") {view=1; drawn=false;}
    if (str == "screen2") {view=2; drawn=false;}
    if (str == "screen3") {view=3; drawn=false;}
    if (str.substring(0, 3) == "OTP") {view=1; drawn=false; strQRCode = str.substring(3, 9);}
    // if (str == "324689") {view=1; drawn=false;}
  }

  // Nhận dữ liệu qua cổng hard Serial (màn hình Serial/ D0 D1)
  if (Serial.available() > 0)
  {
    // Đọc chuỗi truyền xuống đến kí tự '@'
    String str1 = Serial.readStringUntil('@');
    // mySerial.print(str1);

    if (str1 == "-1")      {view=-1; drawn=false;}
    if (str1 == "screen0") {view=0; drawn=false;}
    if (str1 == "screen1") {view=1; drawn=false;}
    if (str1 == "screen2") {view=2; drawn=false;}
    if (str1 == "screen3") {view=3; drawn=false;}
  }

  // Vẽ màn hình hiển thị
  if (!drawn) 
  {
    if (view==-1) ds.displayScreenTest();
    if (view==0) ds.displayScreen_Welcome();
    if (view==1) ds.displayScreen_ScanOTP();
    if (view==2) ds.displayScreen_ChargingVehicle();
    if (view==3) ds.displayScreen_CompletedCharging();
    drawn = true;
  }

}
