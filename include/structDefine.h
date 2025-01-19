#ifndef _STRUCTDEFINE_H
#define _STRUCTDEFINE_H

#include <Arduino.h>
typedef struct
{
    boolean pumpOn, genNewQueueNum, checkPumpDuration;
    volatile uint16_t oneSecond, pumpOnDuration;
    volatile boolean checkSonic;
} pendingResponse_s;

#endif