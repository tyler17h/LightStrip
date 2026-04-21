/* --- LightManager.cpp --- */

/* ------------------------------------------
author: Tyler
date: 4/19/2026
------------------------------------------ */

#include "LightManager.h"

LightManager::LightManager() {
    mode = modesManager.getCurrMode();
    // solid.setLight(light);
    // staticRainbow.setLight(light);
    // rainbowChase.setLight(light);
    
    return;
}

LightManager::~LightManager() {
    // Destructor
}

void LightManager::LightAction(ACTION action) {    
    switch (action)
    {
    case NOTHING:
        break;
    case NEXT:
        mode = modesManager.nextMode();
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

    updateLight();

    return;
}

void LightManager::updateLight() {
    updateColor();
    // updateModif();
}

void LightManager::updateColor() {
    switch (mode)
    {
    case SOLID:
        Serial.println("Show Solid");
        // solid.setColor();
        break;
    case RAINBOW:
        Serial.println("Show Rainbow");
        // staticRainbow.setColor();
    case CHASE:
        Serial.println("Show Chase");
    default:
        break;
    }
}

void LightManager::triggerModifierSignal(ACTION action) {
    
}