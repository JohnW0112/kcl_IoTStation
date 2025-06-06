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
#define ROW1 13
#define ROW2 6
#define ROW3 7
#define ROW4 9
#define COLUMN1 10
#define COLUMN2 14
#define COLUMN3 8

#define ROW_NUM 4
#define COLUMN_NUM 3

/*function*/
void keypad_userInputWaterInit(user_input_s *input);
user_input_e keypad_userInput(user_input_s *input, char key);
void keypad_getResponse(char key, menu_e mNum, pendingResponse_s *r);
#endif