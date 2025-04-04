
#include "Arduino.h"
#include "Wire.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

// **OLED Display**
#define OLED_SCREEN_WIDTH 128
#define OLED_SCREEN_HEIGHT 64
#define OLED_RESET -1
#define BUTTON_PIN 2  

Adafruit_SSD1306 oled(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, &Wire, OLED_RESET);

// **MODE Stwiching**
bool autoMode = true;
unsigned long lastPressTime = 0;
const unsigned long DEBOUNCE_TIME = 50;
const unsigned long DOUBLE_PRESS_INTERVAL = 500;
const unsigned long SHORT_PRESS_TIME = 300;
int lastButtonState = HIGH;
int pressCount = 0;

// **Press time detection**
unsigned long pressStartTime = 0;
const unsigned long PRESS_HOLD_TIME = 500; // 0.5s press time

// **Motor Driver PIN**
#define RUN_FW_PIN 6    // 6
#define STOP_PIN 7      // 8
#define SPEED_PIN 5     // 9

#define PWM_FREQUENCY 2000  
#define PWM_MIN 10     // at 30°
#define PWM_MAX 200        // at 90°

// **Accelerometer**
Adafruit_MMA8451 mma;
bool tiltingUp = false;
unsigned long lastUpdate = 0;
unsigned long lastSerialUpdate = 0;

float prevRoll = 0;
const float ANGLE_THRESHOLD = 2.0;
const float TILT_THRESHOLD = -10.0;
const unsigned long SERIAL_UPDATE_INTERVAL = 500;

// **OLED MODE Display**
void oled_displayMode(Adafruit_SSD1306 *display, bool mode) {
    display->clearDisplay();
    display->setTextSize(2);
    display->setTextColor(WHITE);
    display->setCursor(0, 20);
    display->println(mode ? "AUTO" : "MANUAL");
    display->display();
    Serial.println(mode ? "AUTO mode displayed" : "MANUAL mode displayed");
}

// **Compute PWM Speed**
int calculatePWM(float roll) {
    static int lastPWM = PWM_MIN;
    float startSlope = -30.0;
    float maxSlope = -90.0;

    if (roll > startSlope) return PWM_MIN;
    if (roll < maxSlope) roll = maxSlope;

    float scale = (roll - startSlope) / (maxSlope - startSlope);
    int targetPWM = PWM_MIN + scale * (PWM_MAX - PWM_MIN);

    if (targetPWM > lastPWM) {
        lastPWM += 5;
    } else if (targetPWM < lastPWM) {
        lastPWM -= 5;
    }

    lastPWM = constrain(lastPWM, PWM_MIN, PWM_MAX);
    return lastPWM;
}

void setup() {
    Serial.begin(115200);
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    oled_displayMode(&oled, autoMode);

    if (!mma.begin(0x1C) && !mma.begin(0x1D)) {
        Serial.println("MMA8451 not found! Check wiring.");
        while (1);
    }
    mma.setRange(MMA8451_RANGE_2_G);

    pinMode(RUN_FW_PIN, OUTPUT);
    pinMode(STOP_PIN, OUTPUT);
    pinMode(SPEED_PIN, OUTPUT);

    digitalWrite(RUN_FW_PIN, LOW);
    digitalWrite(STOP_PIN, HIGH);
}

void loop() {
    unsigned long currentTime = millis();
    int buttonState = digitalRead(BUTTON_PIN);

    // **Switching Mode by Button**
    if (buttonState != lastButtonState) {
        if (buttonState == LOW && (currentTime - lastPressTime > DEBOUNCE_TIME)) {
            pressCount++;
            Serial.print("Button pressed. Count: ");
            Serial.println(pressCount);
            lastPressTime = currentTime;
        }
    }
    lastButtonState = buttonState;

    if (pressCount >= 2 && (currentTime - lastPressTime < DOUBLE_PRESS_INTERVAL) && (currentTime - lastPressTime < SHORT_PRESS_TIME)) {
        autoMode = !autoMode;
        oled_displayMode(&oled, autoMode);
        Serial.println(autoMode ? "Switched to AUTO mode" : "Switched to MANUAL mode");
        pressCount = 0;
    }

    if (currentTime - lastPressTime >= DOUBLE_PRESS_INTERVAL) {
        pressCount = 0;
    }

    // **Read Accelerometer Data**
    sensors_event_t event;
    mma.getEvent(&event);

    float ax = event.acceleration.x;
    float ay = event.acceleration.y;
    float az = event.acceleration.z;
    float roll = atan2f(ay, sqrtf(ax * ax + az * az)) * 180.0 / PI;

    if (fabs(roll - prevRoll) > ANGLE_THRESHOLD) {
        prevRoll = roll;
    }

    if (millis() - lastSerialUpdate >= SERIAL_UPDATE_INTERVAL) {
        lastSerialUpdate = millis();
        Serial.print(autoMode ? "[AUTO] " : "[MANUAL] ");
        Serial.print("Angle: ");
        Serial.print(prevRoll);
        Serial.println("°");
    }

    if (autoMode) {
        // **AUTO Mode**
        if (prevRoll < -30) {
            tiltingUp = true;
        } else {
            tiltingUp = false;
        }

        if (tiltingUp) {
            digitalWrite(RUN_FW_PIN, HIGH);
            digitalWrite(STOP_PIN, LOW);
            int pwmValue = calculatePWM(prevRoll);
            analogWrite(SPEED_PIN, pwmValue);
            Serial.print("PWM Speed: ");
            Serial.println(pwmValue);
        } else {
            digitalWrite(RUN_FW_PIN, LOW);
            digitalWrite(STOP_PIN, HIGH);
            analogWrite(SPEED_PIN, 0);
        }
    } else {
        // **MANUAL Mode**
        if (buttonState == LOW) {
            if (pressStartTime == 0) {
                pressStartTime = millis();  // record press time
            }
            if (millis() - pressStartTime >= PRESS_HOLD_TIME) {  // make sure to press and hold the button more than 0.5s
                digitalWrite(RUN_FW_PIN, HIGH);
                digitalWrite(STOP_PIN, LOW);
                int manualPWM = calculatePWM(-30);
                analogWrite(SPEED_PIN, manualPWM);
                Serial.print("MANUAL MODE - Motor ON - Speed: ");
                Serial.println(manualPWM);
            }
        } else {
            pressStartTime = 0;  // reset time count when release the button
            digitalWrite(RUN_FW_PIN, LOW);
            digitalWrite(STOP_PIN, HIGH);
            analogWrite(SPEED_PIN, 0);
        }
    }
}
