#ifndef _STRUCTDEFINE_H
#define _STRUCTDEFINE_H

#include <Arduino.h>
typedef enum
{
    WATER_HIGH = 0,
    WATER_MEDIUM = 1,
    WATER_LOW = 2
} water_level_e;

typedef enum
{
    INPUT_OK,
    INPUT_COMPLETE,
    INPUT_EXIT,
    INPUT_INVALID,
    INPUT_FULL,
} user_input_e;

typedef struct
{
    boolean pumpOn, genNewQueueNum;
    volatile uint16_t oneSecond;
    volatile boolean checkSonic;
} pendingResponse_s;

typedef struct
{
    float fullDistance, emptyDistance, lowLevel, medLevel;
    water_level_e currentWaterLevel;
} water_data_s;

typedef struct
{
    boolean pumpOn;
    uint16_t pumpOnTime;
} pump_s;

typedef struct
{
    uint8_t data[2], index, dataActual;
    boolean backOnce;
} user_input_s;

#endif