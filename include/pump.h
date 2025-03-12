#ifndef _PUMP_H
#define _PUMP_H

/*include*/
#include <Arduino.h>
#include "structDefine.h"

/*define*/
#define PUMP_PIN 2

/*functions*/
void pump_init(pump_s *p);
void pump_dispense(pump_s *p, uint8_t waterAmount);

#endif