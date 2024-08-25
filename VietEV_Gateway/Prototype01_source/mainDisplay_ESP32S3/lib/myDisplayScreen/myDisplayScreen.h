#pragma once
#include <Arduino_GFX_Library.h>
#include <qrcode.h>
#include "myLib.h"

class myDisplayScreen
{
private:
// Do not change this
// ***********************************************************


#if defined(DISPLAY_DEV_KIT)
    Arduino_GFX *gfx = create_default_Arduino_GFX();
#else

    Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
        GFX_NOT_DEFINED, GFX_NOT_DEFINED, GFX_NOT_DEFINED,
        40, 41, 39, 42,
        45, 48, 47, 21, 14,
        5, 6, 7, 15, 16, 4,
        8, 3, 46, 9, 1);

    Arduino_RPi_DPI_RGBPanel *gfx = new Arduino_RPi_DPI_RGBPanel(
        bus,
        480, 0, 8, 4, 43,
        272, 0, 8, 4, 12,
        1, 9000000, true);

#endif
    // ******************************************************************************

public:
    myDisplayScreen();

    void initLCD();

    void displayScreen_Test();

    // Display init gateway screen
    void displayScreen_InitDevice();

    // Display welcome screen
    void displayScreen_Welcome();

    // Display scan QR code screen
    void displayScreen_ScanOTP();

    // Display vehicle is charging screen
    void displayScreen_ChargingVehicle();

    // Display vehicle charging completed screen
    void displayScreen_CompletedCharging();

    // Show all received information from software serial
    void displayScreen_Debugger();

    void drawQRCode(QRCode *qrcode, int x, int y, int pixelSize);
};