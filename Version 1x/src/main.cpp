#include <Arduino.h>
#include <ButtonManager.h>
#include <LightManager.h>
#include <SystemState.h>
#include "ActionEnum.h"

ButtonManager buttonManager;
LightManager lightManager;
SystemManager systemManager;
ACTION action = NOTHING;
ACTION setAction = NOTHING;
bool actionSetFlag = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  action = buttonManager.getButtonAction();
  delay(1);
  
  if (action == SHUTDOWN && systemManager.isSystemOnline()) {
    Serial.println("SHUTTING DOWN");
    systemManager.powerOffSystem();
    lightManager.shutdown();
    actionSetFlag = false;
  }
  else if (systemManager.isSystemOnline()) {
    lightManager.LightAction(action);
  }
  
  if (action != NOTHING && action != SHUTDOWN) { actionSetFlag = true; }
  if (actionSetFlag == true) { 
    setAction = action;
    if (buttonManager.isPressed() == false) {
      actionSetFlag = false;  
      String str = "action:" + String(action) + " | is pressed:" + String(buttonManager.isPressed());
      Serial.println(str);
      if (systemManager.isSystemOffline()) {
        Serial.println("BOOTING UP");
        systemManager.powerOnSystem();
      }
      else {
        lightManager.performAction(setAction);
      }
    }
  }
}