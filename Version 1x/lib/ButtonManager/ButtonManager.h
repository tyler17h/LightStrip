/* --- ButtonManager.h --- */

/* ------------------------------------------
Author: Tyler
Date: 3/20/2026
------------------------------------------ */

#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H
#include <Arduino.h>
#include "ActionEnum.h"

class ButtonManager {
public:
    ButtonManager();
    ~ButtonManager();
    bool isPressed();
    ACTION determineAction();
    
private:
    int pin = 2;
    unsigned long initPressedTime = 0;
    bool isInitSet = false;
    ACTION action = NOTHING;
};

#endif // BUTTONMANAGER_H
