#include <Arduino.h>
#include <ButtonManager.h>
#include <LightManager.h>
#include "ActionEnum.h"

ButtonManager buttonManager;
LightManager lightManager;
ACTION action = NOTHING;

void setup() {
  Serial.begin(9600);
}

void loop() {
    action = buttonManager.determineAction();
    delay(1);
    Serial.println("main loop");

    // lightManager.LightAction(action);
}