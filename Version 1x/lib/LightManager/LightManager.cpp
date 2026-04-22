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
    //track the action the user is going to take

    if (action != NOTHING) {
        lastAction = action;
        checkForModifierTrigger();
    }
    else {
        //only execute if there is an action being made
        if (lastAction != NOTHING) {
            performAction();
            lastAction = NOTHING;
        }
    }

    //regardless of the action update the current light settings 
    updateLight();

    return;
}

void LightManager::checkForModifierTrigger() {
    //trigger the modifer signal flag
    switch (lastAction)
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
        default:
        break;
    }
    
    if (isModifierSignalActiveFlag) {
        modifierSignal();
    }

    return;
}

void LightManager::modifierSignal() {
    if (lastAction == lastModifier) {
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

void LightManager::performAction() {
    switch (lastAction)
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
    case SHUTDOWN:
        //reached the end of the command list.  shutdown and enter low power mode
        Serial.println("Shutdown triggered");
        // shutDown();
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

void LightManager::triggerModifierSignal(ACTION action) {
    
}