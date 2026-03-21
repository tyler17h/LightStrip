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
    ButtonManager(int _pin);
    ~ButtonManager();
    bool isPressed();
    ACTION determineAction();
    
private:
    int pin;
    unsigned long initPressedTime = 0;
    bool isInitSet = false;
    ACTION action = NOTHING;
};

#endif // BUTTONMANAGER_H
