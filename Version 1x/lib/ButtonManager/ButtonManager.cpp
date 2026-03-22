/* --- ButtonManager.cpp --- */

/* ------------------------------------------
author: Tyler
date: 3/20/2026
------------------------------------------ */

#include "ButtonManager.h"
#include <Adafruit_NeoPixel.h>

ButtonManager::ButtonManager() {
    // Constructor
    pinMode(pin, INPUT_PULLUP);
}

ButtonManager::~ButtonManager() {
    // Destructor
}

bool ButtonManager::isPressed() {
    if (digitalRead(pin) == LOW) {
        return true;
    }
    else {
        isInitSet = false;
        return false;
    }
}

ACTION ButtonManager::determineAction() {
    if (!isPressed()) {
        action = NOTHING;
        return action;
    }

    if (!isInitSet) {
        initPressedTime = millis();
        isInitSet = true;
    }

    unsigned long timePressed = millis() - initPressedTime;
    if (timePressed < 50) {
        action = NOTHING;
    }
    else if (timePressed >= 50 && timePressed < 500) {
        action = NEXT;
    }
    else if (timePressed >= 500 && timePressed < 2000) {
        action = UNIQUE_MODIFIER;
    }
    else if (timePressed >= 2000 && timePressed < 3000) {
        action = BREATH_MODIFIER;
    }
    else if (timePressed >= 3000 && timePressed < 4500) {
        action = STROBE_MODIFIER;
    }
    else {
        action = SHUTDOWN;
    }
    
    return action;
}