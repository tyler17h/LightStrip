/* --- Task.h --- */

/* ------------------------------------------
Author: Tyler
Date: 4/19/2026
------------------------------------------ */

#ifndef TASK_H
#define TASK_H
#include "TaskEnum.h"

class Task {
public:
    Task(unsigned int time, TASK task, unsigned int intervals);
    ~Task();
    unsigned int time;
    TASK task;
    unsigned int intervals;

private:

};

#endif // TASK_H
