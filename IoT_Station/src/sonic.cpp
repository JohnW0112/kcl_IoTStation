#include "sonic.h"

/*Private functions*/
static uint16_t sonic_getReading()
{
    float duration;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    // distance in cm = (duration / 1000 000 * 340) /2 * 100
    return (uint16_t)(duration * 0.017);
}

static void sonic_updateLevels(water_data_s *data)
{
    float steps = (data->emptyDistance - data->fullDistance) / 100;

    // low water level when less than 30%
    data->lowLevel = data->emptyDistance - (steps * 30);

    // Medium water level when less than 70%
    data->medLevel = data->emptyDistance - (steps * 70);
}

/*public Functions*/
void sonic_init(water_data_s *data)
{
    Serial.println("Initilising ultrasonic sensor...");
    pinMode(TRIG_PIN, OUTPUT);
    digitalWrite(TRIG_PIN, LOW);
    pinMode(ECHO_PIN, INPUT);

    data->fullDistance = DEFAULT_FULL_DISTANCE;
    data->emptyDistance = DEFAULT_EMPTY_DISTANCE;

    sonic_updateLevels(data);
    sonic_updateCurrentLevel(data);
    Serial.println("Ultrasonic sensor initilisation completed.");
}

void sonic_setZeroLevel(water_data_s *data)
{
    data->emptyDistance = sonic_getReading();
    sonic_updateLevels(data);
}

void sonic_setFullLevel(water_data_s *data)
{
    data->fullDistance = sonic_getReading();
    sonic_updateLevels(data);
}

void sonic_updateCurrentLevel(water_data_s *data)
{
    uint16_t reading;
    reading = sonic_getReading();
    Serial.print("Sonic Reading: ");
    Serial.println(reading);

    if (reading >= data->lowLevel)
    {
        data->currentWaterLevel = WATER_LOW;
        Serial.println(data->lowLevel);
        return;
    }
    if (reading >= data->medLevel)
    {
        data->currentWaterLevel = WATER_MEDIUM;
        Serial.println("WATER MEDIUM");
        return;
    }
    Serial.println("WATER HIGH");
    data->currentWaterLevel = WATER_HIGH;
}
