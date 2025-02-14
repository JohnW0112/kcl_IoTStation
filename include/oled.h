#ifndef _OLED_H
#define _OLED_H

/*header files*/
#include "Arduino.h"
#include "Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "sonic.h"

/*defines*/
#define OLED_SCREEN_WIDTH 128 // OLED display width, in pixels
#define OLED_SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// Main menu
#define OLED_WATER_LEVEL_TAG_CURSOR 0, 0
#define OLED_QUEUE_STATUS_TAG_CURSOR 0, 16

#define OLED_WATER_LEVEL_CURSOR 0, 8
#define OLED_QUEUE_STATUS_CURSOR 0, 32

#define OLED_GET_WATER_CURSOR 0, 40
#define OLED_GET_TICKET_CURSOR 0, 48

// pumping
#define OLED_PUMPING_CURSOR 40, 20

/*Variable*/

/*typdefs*/
typedef enum
{
  MAIN_MENU,
  WANTED_WATER,
  DISPENSING_WATER,
  DISPLAY_CURRENT_QUEUE_NUM,
  DISPLAY_NEW_QUEUE_NUM
} menu_e;

/*function*/
boolean oled_init(Adafruit_SSD1306 *display);
void oled_updateWaterLevel(Adafruit_SSD1306 *display, water_level_e level);
void oled_updateQueue(Adafruit_SSD1306 *display, water_level_e level);
void oled_display(Adafruit_SSD1306 *display, menu_e mNum);
#endif