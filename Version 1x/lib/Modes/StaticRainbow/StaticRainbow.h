/* --- StaticRainbow.h --- */

/* ------------------------------------------
Author: Tyler
Date: 4/17/2026
------------------------------------------ */

#ifndef STATICRAINBOW_H
#define STATICRAINBOW_H
#include <Mode/Mode.h>

class StaticRainbow : public Mode {
public:
    StaticRainbow();
    ~StaticRainbow();
    // void setColor() override;

private:
    int reps = 1;
};

#endif // STATICRAINBOW_H
