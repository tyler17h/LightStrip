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
    updateLight();
    if (action != NOTHING) {
        checkForTriggers(action);
    }
    return;
}

void LightManager::checkForTriggers(ACTION action) {
    //trigger the modifer signal flag
    switch (action)
    {
    case UNIQUE_MODIFIER:
        if (!isModifierSignalActiveFlag) {
            Serial.println("Trigger Modify Signal 1");
            isModifierSignalActiveFlag = true;
            lastModifier = UNIQUE_MODIFIER;
        }
        break;
    case BREATH_MODIFIER:
        if (!isModifierSignalActiveFlag) {
            Serial.println("Trigger Modify Signal 2");
            isModifierSignalActiveFlag = true;
            lastModifier = BREATH_MODIFIER;
        }
        break;
    case STROBE_MODIFIER:
        if (!isModifierSignalActiveFlag) {
            Serial.println("Trigger Modify Signal 3");
            isModifierSignalActiveFlag = true;
            lastModifier = STROBE_MODIFIER;
        }
        break;
    case SHUTDOWN:
        Serial.println("Shutdown triggered");
        break;
    default:
        break;
    }
    
    if (isModifierSignalActiveFlag) {
        modifierSignal(action);
    }

    return;
}

void LightManager::modifierSignal(ACTION action) {
    if (action == lastModifier) {
        isModifierSignalActiveFlag = true;
        modifySignalWaitTime = millis();
        // light.clearStrip();
        // light.showStrip();
    }
    if (scheduler.hasWaited(350, modifySignalWaitTime)) {
        // fillStrip();
        isModifierSignalActiveFlag = false;
    }
}

void LightManager::performAction(ACTION action) {
    switch (action)
    {
    case NEXT:
        Serial.println("Next mode");
        mode = modesManager.nextMode();
        break;
    case UNIQUE_MODIFIER:
        //trigger the modifer signal flag
        Serial.println("Unique modifier triggered");
        // triggerModifierSignal(action);
        // setUniqueModifier();
        break;
    case BREATH_MODIFIER:
        //trigger the modifer signal flag
        Serial.println("Breath modifier triggered");
        // triggerModiferSignal(action);
        // setBreathModifier();
        break;
    case STROBE_MODIFIER:
        //trigger the modifer signal flag
        Serial.println("Strobe modifier triggered");

        // triggerModiferSignal(action);
        // setStrobeModifier();
        break;
    default:
        break;
    }

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
        // solid.setColor();
        break;
    case RAINBOW:
        // staticRainbow.setColor();
        break;
    case CHASE:
        break;
    default:
        break;
    }
}

void LightManager::shutdown() {
    light.clearStrip();
}