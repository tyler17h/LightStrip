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
    case UNIQUE_MODIFIER:
        adaFruit.triggerModiferSignal(UNIQUE_MODIFIER);
        if (!button.isPressed()) {
            adaFruit.setUniqueModifier();
        }
        break;
    case BREATH_MODIFIER:
        adaFruit.triggerModiferSignal(BREATH_MODIFIER);
        if (!button.isPressed()) {
            adaFruit.setBreathModifier();
        }
        break;
    case STROBE_MODIFIER:
        adaFruit.triggerModiferSignal(STROBE_MODIFIER);
        if (!button.isPressed()) {
            adaFruit.setStrobeModifier();
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