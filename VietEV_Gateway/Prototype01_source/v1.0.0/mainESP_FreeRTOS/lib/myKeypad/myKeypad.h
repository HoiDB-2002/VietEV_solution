#pragma once

#include "myLib.h"
#include <Wire.h>
#include <PCF8575.h>

class myKeypad
{
private:
    PCF8575 pcf8575;
    int lastKey = -1; // To store the last key pressed

public:
    myKeypad();
    ~myKeypad();
    
    void initKeypad();
    int scanMatrix();
};
