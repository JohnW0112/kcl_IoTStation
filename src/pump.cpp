#include "pump.h"

void pump_init(pump_s *p)
{
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, LOW);

    p->pumpOn = false;
    p->timeConfigured = false;
    p->pumpOnTime = 0;
}

void pump_dispense(pump_s *p)
{
    if (p->timeConfigured == false || p->pumpOn == false)
        return;
    // The flow rate of the pump is 32L/min
    digitalWrite(PUMP_PIN, HIGH);
    delay(p->pumpOnTime * 1000);
    digitalWrite(PUMP_PIN, LOW);

    p->pumpOn = false;
    p->timeConfigured = false;
}