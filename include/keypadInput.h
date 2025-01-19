#ifndef _KEYPADINPUT_H
#define _KEYPADINPUT_H

#include <Arduino.h>
#include <Keypad.h>
#include "oled.h"
#include "structDefine.h"
/*extern variable*/
extern Keypad keypad;

extern pendingResponse_s response;
/*Keypad pinouts*/
#define ROW1 PIN_PB23
#define ROW2 PIN_PA21
#define ROW3 PIN_PA16
#define ROW4 PIN_PB22
#define COLUMN1 PIN_PA17
#define COLUMN2 PIN_PA21
#define COLUMN3 PIN_PA20

#define ROW_NUM 4
#define COLUMN_NUM 3

/*function*/
void keypad_getResponse(char key, menu_e mNum, pendingResponse_s *r);
#endif