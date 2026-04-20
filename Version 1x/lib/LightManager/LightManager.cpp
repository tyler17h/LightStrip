/* --- LightManager.cpp --- */

/* ------------------------------------------
author: Tyler
date: 4/19/2026
------------------------------------------ */

#include "LightManager.h"

LightManager::LightManager() {
    mode = modesManager.getCurrMode();

    return;
}

LightManager::~LightManager() {
    // Destructor
}

void LightManager::LightAction(ACTION action) {
    Serial.println("Light manager start");

    switch (action)
    {
    case NOTHING:
        break;
    case NEXT:
        // mode = modesManager.nextMode();
        break;
    case UNIQUE_MODIFIER:
        // triggerModifierSignal(action);
        // setUniqueModifier();
        break;
    case BREATH_MODIFIER:
        // triggerModiferSignal(action);
        // setBreathModifier();
        break;
    case STROBE_MODIFIER:
        // triggerModiferSignal(action);
        // setStrobeModifier();
        break;
    case SHUTDOWN:
        // shutDown();
        break;
    default:
        break;
    }

    Serial.print("Action");
    updateLight();

    return;
}

void LightManager::updateLight() {
    Serial.println("Update");
    updateColor();
    // updateModif();
}

void LightManager::updateColor() {
    Serial.print(mode);
    switch (mode)
    {
    case SOLID:
        Serial.println("Solid set color");
        solid.setColor();
        break;
    
    default:
        break;
    }
}

void LightManager::triggerModifierSignal(ACTION action) {
    
}