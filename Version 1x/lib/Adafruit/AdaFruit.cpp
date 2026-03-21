/* --- AdaFruit.cpp --- */

/* ------------------------------------------
author: Tyler
date: 3/20/2026
------------------------------------------ */

#include "AdaFruit.h"

AdaFruit::AdaFruit() {
    // Constructor
    strip.begin();
    strip.setBrightness(baseBrightness);
}

AdaFruit::~AdaFruit() {
    // Destructor
}

void AdaFruit::turnOn() {
    fillStrip();
}

void AdaFruit::shutDown() {
    isPowered = false;
    initModify_1_Trigger = false;
    initModify_2_Trigger = false;
    strip.clear();
    strip.show();
}

void AdaFruit::nextColor() {
    if (isPowered) {
        modify_1_activeFlag = false;
        modify_2_activeFlag = false;
        brightness = baseBrightness;
        strip.setBrightness(brightness);
        lightmode = (lightmode + 1) % MODE_LIST_SIZE;
        fillStrip();
    }
    else {
        isPowered = true;
        fillStrip();
    } 
}

void AdaFruit::fillStrip() {
    if (scheduler.hasWaited(10, fillWaitTime)) {
        fillWaitTime = millis();

        if (modify_1_activeFlag) {
            modify_1_Effect();
        }
        if (modify_2_activeFlag) {
            modify_2_Effect();
        }

        switch (lightmode)
        {
        case SOLID:
            setSolid();
            strip.fill(currentColor);
            break;
        case RAINBOW:
            setRainbow();
            break;
        case CHASE:
            setTheaterChaseRainbow();
            break;
        default:
            break;
        }
        strip.show();
    }
}

void AdaFruit::setSolid() {
    currentColor = strip.Color(100, 100, 100);
}

void AdaFruit::setRainbow() {
    strip.rainbow(0, 1, 255, 150, true);
}

void AdaFruit::setTheaterChaseRainbow() {
    // Hue of first pixel runs 5 complete loops through the color wheel.
    // Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
    // means we'll make 5*65536/256 = 1280 passes through this loop:
    firstPixelHue = (firstPixelHue += 256) % maxFirstPixelHue;
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
}

void AdaFruit::modify_1_Effect() {
    if (scheduler.hasWaited(25, modifer_1_WaitTime)) {
        if (isIncremneting) {
            brightness++;
            strip.setBrightness(brightness);
            
            isIncremneting = (brightness >= maxBrightness) ? false : true;
        } else {
            brightness--;
            strip.setBrightness(brightness);
            
            isIncremneting = (brightness <= 0) ? true : false;
        }
    }
}

void AdaFruit::modify_2_Effect() {
    if (scheduler.hasWaited(2000, modifer_1_WaitTime)) {
        if (isIncremneting) {
            brightness = maxBrightness;
            strip.setBrightness(brightness);
            
            isIncremneting = (brightness == maxBrightness) ? false : true;
        } else {
            brightness = 0;
            strip.setBrightness(brightness);
            
            isIncremneting = (brightness == 0) ? true : false;
        }
    }
}

void AdaFruit::triggerModify_1_signal() {
    if (!initModify_1_Trigger) {
        modifySignalWaitTime = millis();
        initModify_1_Trigger = true;
        Serial.println("clear");
        strip.clear();
        strip.show();
    }
    if (scheduler.hasWaited(350, modifySignalWaitTime)) {
        Serial.println("lit");
        fillStrip();
    }
}

void AdaFruit::SetModifier_1() {
    initModify_1_Trigger = false;
    modify_1_activeFlag = true;
}

void AdaFruit::triggerModify_2_signal() {
    if (!initModify_2_Trigger) {
        initModify_1_Trigger = false;
        modifySignalWaitTime = millis();
        initModify_2_Trigger = true;
        Serial.println("clear");
        strip.clear();
        strip.show();
    }
    if (scheduler.hasWaited(350, modifySignalWaitTime)) {
        Serial.println("lit");
        fillStrip();
    }
}

void AdaFruit::SetModifier_2() {
    modify_1_activeFlag = false;
    initModify_2_Trigger = false;
    modify_2_activeFlag = true;
}

