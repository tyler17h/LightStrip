/* --- LightManager.h --- */

/* ------------------------------------------
Author: Tyler
Date: 4/19/2026
------------------------------------------ */

#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H
#include <Arduino.h>
#include <Light.h>
#include "ActionEnum.h"
#include <Scheduler.h>
#include <ModesManager.h>
#include <Light.h>
#include <Solid/Solid.h>
#include <StaticRainbow/StaticRainbow.h>
#include <RainbowChase/RainbowChase.h>

class LightManager {
public:
    LightManager();
    ~LightManager();
    void LightAction(ACTION action);
    void checkForTriggers(ACTION action);
    void modifierSignal(ACTION action);
    void performAction(ACTION action);
    void updateLight();
    void updateColor();
    void shutdown();
    
private:
    Scheduler scheduler; 
    ModesManager modesManager;
    LIGHTMODE mode;
    Light light;
    ACTION lastAction;
    
    bool isModifierSignalActiveFlag = false;
    unsigned long int modifySignalWaitTime = 0;
    ACTION lastModifier = NOTHING;
    // Solid solid;
    // StaticRainbow staticRainbow;
    // RainbowChase rainbowChase;
};

#endif // LIGHTMANAGER_H
