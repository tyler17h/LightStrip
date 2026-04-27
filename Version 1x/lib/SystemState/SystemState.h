/* --- SystemState.h --- */

/* ------------------------------------------
Author: Tyler
Date: 4/26/2026
------------------------------------------ */

#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H
#include "SystemStateEnum.h"

class SystemManager {
public:
    SystemManager();
    ~SystemManager();
    void powerOnSystem();
    void powerOffSystem();
    bool isSystemOnline() { return systemState == ONLINE; }
    bool isSystemOffline() { return systemState == OFFLINE; }
    SYSTEMSTATE getSystemState() { return systemState; }
private:
    SYSTEMSTATE systemState = OFFLINE;
};

#endif // SYSTEMSTATE_H
