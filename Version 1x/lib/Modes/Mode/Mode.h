/* --- Mode.h --- */

/* ------------------------------------------
Author: Tyler
Date: 4/19/2026
------------------------------------------ */

#ifndef MODE_H
#define MODE_H
#include <Adafruit_NeoPixel.h>
#include <Light.h>
#include <Scheduler.h>

class Mode {
public:
    Mode();
    ~Mode();
    void setColor();
    virtual void uniqueModifier();
    
    Light* light;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint16_t hue;
    uint16_t hueStep = 65535 / 17;
    uint32_t color;

    Scheduler* scheduler;
    unsigned long int uniqueModiferWaitTime;
private:

};

#endif // MODE_H
