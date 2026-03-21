#include <Arduino.h>
#include <ButtonManager.h>
#include <AdaFruit.h>
#include <Scheduler.h>

#include "ActionEnum.h"

ButtonManager button;
AdaFruit adaFruit;
Scheduler scheduler;
ACTION action = NOTHING;
bool isButtonBeingHeld = false;
unsigned long initWaitTime = 0;
bool Modify_1_flagSet = false;
bool Modify_2_flagSet = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
    action = button.determineAction();
    delay(1);
    switch (action)
    {
    case NOTHING:
        adaFruit.fillStrip();
        break;
    case NEXT:
        if (!button.isPressed()) {
            adaFruit.nextColor();
        }
        break;
    case MODIFY_1:
        adaFruit.triggerModify_1_signal();
        if (!button.isPressed()) {
            adaFruit.SetModifier_1();
        }
        break;
    case MODIFY_2:
        adaFruit.triggerModify_2_signal();
        if (!button.isPressed()) {
            adaFruit.SetModifier_2();
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