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


void handleShutdown() {
  Serial.println("SHUTTING DOWN");
  systemManager.powerOffSystem();
  lightManager.shutdown();
  actionSetFlag = false;
}

void updateLightManager() {
    lightManager.LightAction(action);
}

void handleAction() {
  if (action != NOTHING && action != SHUTDOWN) { 
    actionSetFlag = true; 
  }
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

void loop() {
  action = buttonManager.getButtonAction();
  delay(1);
  
  if (action == SHUTDOWN && systemManager.isSystemOnline()) {
    handleShutdown();
  }
  else if (systemManager.isSystemOnline()) {
    updateLightManager();
  }
  
  handleAction();
  
}