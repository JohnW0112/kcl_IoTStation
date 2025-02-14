#include "keypadInput.h"

/*Keypad initilization*/
char hexaKeys[ROW_NUM][COLUMN_NUM] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

uint8_t rowPins[ROW_NUM] = {ROW1, ROW2, ROW3, ROW4};
uint8_t columnPins[COLUMN_NUM] = {COLUMN1, COLUMN2, COLUMN3};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, columnPins, ROW_NUM, COLUMN_NUM);

/*public functions*/
void keypad_getResponse(char key, menu_e mNum, pendingResponse_s *r)
{
    // TODO: Implemnent wanted water input
    switch (mNum)
    {
    case MAIN_MENU:
        // want water
        if (key == '1')
        {
            r->pumpOn = true;
        }
        // new queue number
        if (key == '2')
        {
            r->genNewQueueNum = true;
        }
        break;
    case WANTED_WATER:
        // Echo input
        break;
    case DISPENSING_WATER:
        // no action
        break;
    case DISPLAY_CURRENT_QUEUE_NUM:
        // no action
        break;
    case DISPLAY_NEW_QUEUE_NUM:
        // no action
        break;
    }
}