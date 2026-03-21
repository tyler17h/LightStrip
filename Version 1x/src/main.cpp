#include <Arduino.h>
#include <ButtonManager.h>
#include <AdaFruit.h>
#include "ActionEnum.h"

#define STRIP_PIN 4
#define BUTTON_PIN 2


ButtonManager button(BUTTON_PIN);
AdaFruit adaFruit(STRIP_PIN);
ACTION action = NOTHING;
bool isButtonBeingHeld = false;
unsigned long initWaitTime = 0;

bool waitDone(unsigned long waitTime) {
    if (millis() - initWaitTime >= waitTime) {
        initWaitTime = millis();
        return true;
    } 
    return false;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
    action = button.determineAction();
    delay(1);
    switch (action)
    {
    case NOTHING:
        if (waitDone(10)) {
            adaFruit.fillStrip();
        }
        break;
    case NEXT:
        if (!button.isPressed()) {
            adaFruit.nextColor();
        }
        break;
    case MODIFY_1:
        if (!button.isPressed()) {
        }
        break;
    case MODIFY_2:
        if (!button.isPressed()) {
        }
        break;
    case SHUTDOWN:
        adaFruit.shutDown();
        while(!button.isPressed());
        break;    
    default:
        break;
    }
}