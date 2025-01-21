#ifndef _STRUCTDEFINE_H
#define _STRUCTDEFINE_H

#include <Arduino.h>
typedef enum
{
    WATER_HIGH = 0,
    WATER_MEDIUM = 1,
    WATER_LOW = 2
} water_level_e;

typedef struct
{
    boolean pumpOn, genNewQueueNum, checkPumpDuration;
    volatile uint16_t oneSecond, pumpOnDuration;
    volatile boolean checkSonic;
} pendingResponse_s;

typedef struct
{
    uint8_t fullDistance, emptyDistance, lowLevel, medLevel;
    water_level_e currentWaterLevel;
} water_data_s;

#endif