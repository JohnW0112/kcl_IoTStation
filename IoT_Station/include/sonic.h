#ifndef SONIC_H_
#define SONIC_H_

/*Includes*/
#include <Arduino.h>
#include "structDefine.h"

/*Defines*/
#define TRIG_PIN 0
#define ECHO_PIN 1

// Assuming sensor is on top of the barrel, I am leaving 15cm clearance
#define DEFAULT_FULL_DISTANCE 15
// assume the height from top of the barrel to the bottom is about 65cm
#define DEFAULT_EMPTY_DISTANCE 65

/*functions*/
void sonic_init(water_data_s *data);
void sonic_setZeroLevel(water_data_s *data);
void sonic_setFullLevel(water_data_s *data);
void sonic_updateCurrentLevel(water_data_s *data);
#endif