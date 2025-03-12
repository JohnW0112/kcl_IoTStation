#ifndef _OLED_H
#define _OLED_H

/*header files*/
#include <string>
#include "Arduino.h"
#include "Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "sonic.h"
#include "queue.h"

/*defines*/
#define OLED_SCREEN_WIDTH 128 // OLED display width, in pixels
#define OLED_SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// Main menu
#define OLED_WATER_LEVEL_TAG_CURSOR 0, 0
#define OLED_QUEUE_STATUS_TAG_CURSOR 0, 16

#define OLED_WATER_LEVEL_CURSOR 0, 8
#define OLED_QUEUE_STATUS_CURSOR 0, 24

#define OLED_GET_WATER_CURSOR 0, 40
#define OLED_GET_TICKET_CURSOR 0, 48

// pumping
#define OLED_PUMPING_CURSOR 0, 20

// Show new queue num
#define OLED_NEW_QUEUE_NUM_TAG_CURSOR 0, 20
#define OLED_NEW_QUEUE_NUM_CURSOR 0, 36

// Echo user input water amount
#define OLED_ECHO_WATER_AMOUNT_TAG_CURSOR 0, 0
#define OLED_ECHO_WATER_AMOUNT_CURSOR 0, 8

// Notify user queue is full
#define OLED_NOTIFY_QUEUE_FULL_TAG_CURSOR 0, 20

// Notify user invalid input
#define OLED_NOTIFY_INVALID_INPUT_TAG_CURSOR 0, 20

/*typdefs*/
typedef enum
{
  MAIN_MENU,
  WANTED_WATER,
  DISPENSING_WATER,
  DISPLAY_NEW_QUEUE_NUM,
  NOTIFY_QUEUE_FULL,
  NOTIFY_INVALID_INPUT,
} menu_e;

/*function*/
boolean oled_init(Adafruit_SSD1306 *display);
void oled_echoUserInput(Adafruit_SSD1306 *display, user_input_s *input);
void oled_updateWaterLevel(Adafruit_SSD1306 *display, water_level_e level);
void oled_updateQueue(Adafruit_SSD1306 *display, queue_s *q);
void oled_display(Adafruit_SSD1306 *display, menu_e mNum, queue_s *q = nullptr, water_data_s *water = nullptr, uint16_t displayQueueNum = 0);
#endif