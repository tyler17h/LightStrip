/* --- ModesManager.h --- */

/* ------------------------------------------
Author: Tyler
Date: 4/19/2026
------------------------------------------ */

#ifndef MODESMANAGER_H
#define MODESMANAGER_H
#include "ModesEnum.h"



class ModesManager {
public:
    ModesManager();
    ~ModesManager();
    LIGHTMODE getCurrMode() { return lightModes[currMode]; }
    LIGHTMODE nextMode();

private:
    LIGHTMODE lightModes[MODE_LIST_SIZE] = { SOLID, RAINBOW, CHASE };
    int currMode = 0;
};

#endif // MODESMANAGER_H
