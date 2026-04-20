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
    void updateLight();
    void updateColor();
    void triggerModifierSignal(ACTION action);
    
private:
    ModesManager modesManager;
    LIGHTMODE mode;
    Light light;

    Solid solid;
    StaticRainbow staticRainbow;
    RainbowChase rainbowChase;
};

#endif // LIGHTMANAGER_H
