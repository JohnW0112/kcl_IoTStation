#include <Arduino.h>
#include "oled.h"
#include "pump.h"
#include "sonic.h"
#include "queue.h"
#include "keypadInput.h"
#include "structDefine.h"

/*define*/
#define COUNTER_PERIOD 0xB71B

/*variables*/
char keyPress;
volatile uint8_t oneSecond;
pendingResponse_s response;
queue_s q;
menu_e menuNumber;
Adafruit_SSD1306 display(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, &Wire, OLED_RESET);

void pendingReponseInit()
{
  response.genNewQueueNum = false;
  response.pumpOn = false;
  response.pumpOnDuration = 0;
  response.checkSonic = false;
  response.checkPumpDuration = false;
}

void TC5_Handler(void)
{
  oneSecond++;
  Serial.print(oneSecond);
  Serial.print(" Sec\n");
  if (oneSecond == 60)
  {
    response.checkSonic = true;
    oneSecond = 0;
  }
  // clear interrupt flag
  TC5->COUNT16.INTFLAG.bit.MC0 = 1;
}

void timer2Init()
{
  GCLK->CLKCTRL.reg = (uint16_t)(GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(GCM_TC4_TC5));
  while (GCLK->STATUS.bit.SYNCBUSY)
    ;

  // reset TC5
  TC5->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
  while (TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY)
    ;
  while (TC5->COUNT16.CTRLA.bit.SWRST)
    ;

  // Config as 16 bit counter
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT16;
  // Match frequency
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;
  // Prescalar at 1024, 48Mhz / 1024 = 46.875kHz
  // Max timer period 1.3981s
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024 | TC_CTRLA_ENABLE;

  // Set CC Compare, interrupt every 1 sec
  TC5->COUNT16.CC[0].reg = (uint16_t)(COUNTER_PERIOD);
  while (TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY)
    ;

  // Configure interrupt
  NVIC_DisableIRQ(TC5_IRQn);
  NVIC_ClearPendingIRQ(TC5_IRQn);
  NVIC_SetPriority(TC5_IRQn, 0);
  NVIC_EnableIRQ(TC5_IRQn);

  // Enable TC5 interrupt
  TC5->COUNT16.INTENSET.bit.MC0 = 1;
  while (TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY)
    ;
}

void displayInit()
{
  oled_init(&display);
  Serial.println("Display Initialized!");
  menuNumber = MAIN_MENU;
  oled_display(&display, menuNumber);
}

void setup()
{
  // hardware init
  Serial.begin(115200);
  displayInit();

  // software init
  pendingReponseInit();

  // enable 1 sec counter
  timer2Init();
  Serial.println("Setup Completed!");
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
}

void loop()
{
  // When a key press is detected
  keyPress = keypad.getKey();
  if (keyPress)
  {
    keypad_getResponse(keyPress, menuNumber, &response);
  }

  // Check water level every 1 minute
  if (response.checkSonic)
  {
    // TODO: Check water level
    Serial.println("Water level check beginning...");

    response.checkSonic = false;
    Serial.println("Water level check completed!");
  }

  // Turns pump on if user is present
  if (response.pumpOn == true)
  {
    // TODO: Turn on pump
    Serial.println("Pumping in progress...");
    response.checkPumpDuration = true;

    // update screen
    menuNumber = DISPENSING_WATER;
    oled_display(&display, menuNumber);

    Serial.println("Pumping completed!");
    response.checkPumpDuration = true;
    response.pumpOn = false;
  }

  // Generate new queue number
  if (response.genNewQueueNum == true)
  {
    // TODO: Generate new queue num
  }
}
