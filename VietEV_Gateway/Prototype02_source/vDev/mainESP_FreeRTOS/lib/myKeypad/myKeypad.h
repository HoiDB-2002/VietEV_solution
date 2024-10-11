#pragma once

#include "myLib.h"
#include <Adafruit_PCF8574.h>

class myKeypad
{
private:
    Adafruit_PCF8574 pcf;
    int lastKey = -1; // To store the last key pressed

public:
    myKeypad();
    ~myKeypad();
    void initKeypad();
    int scanMatrix();
};
