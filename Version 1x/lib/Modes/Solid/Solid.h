/* --- Solid.h --- */

/* ------------------------------------------
Author: Tyler
Date: 4/17/2026
------------------------------------------ */

#ifndef SOLID_H
#define SOLID_H
#include <Mode/Mode.h>

class Solid : public Mode {
public:
    Solid(Light &_light);
    ~Solid();
    void uniqueModifier() override; 
private:
    
};

#endif // SOLID_H
