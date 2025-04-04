#include "pump.h"

void pump_init(pump_s *p)
{
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, LOW);

    p->pumpOn = false;
    p->pumpOnTime = 0;
}

void pump_dispense(pump_s *p, uint8_t waterAmount)
{
    // The flow rate of the pump is 32L/min
    p->pumpOnTime = waterAmount * 1875;
    digitalWrite(PUMP_PIN, HIGH);
    delay(p->pumpOnTime);
    digitalWrite(PUMP_PIN, LOW);

    p->pumpOn = false;
}