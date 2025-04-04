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
void keypad_userInputWaterInit(user_input_s *input)
{
    input->backOnce = false;
    input->data[0] = 0;
    input->data[1] = 0;
    input->index = 0;
}

user_input_e keypad_userInput(user_input_s *input, char key)
{
    // user press backspace
    Serial.println(key);
    if (key == '*')
    {
        // user pressed back once in an empty array
        if (input->index == 0 && input->backOnce == false)
        {
            input->backOnce = true;
            return INPUT_OK;
        }
        // user pressed twice in an empty array, exiting
        if (input->index == 0 && input->backOnce == true)
        {
            input->backOnce = false;
            return INPUT_EXIT;
        }
        // user wish to delete an entry
        input->index = input->index - 1;
        return INPUT_OK;
    }
    // user press enter
    if (key == '#')
    {
        uint8_t data = 0;
        for (uint8_t i = input->index; i > 0; i--)
        {
            data += (uint8_t)pow(10, (i - 1)) * input->data[input->index - i];
        }

        // invalid entry
        if (data <= 0 || data > 20)
            return INPUT_INVALID;

        // else successful entry
        input->dataActual = data;
        return INPUT_COMPLETE;
    }
    // user press any other key (0-9)
    if (input->index == 2)
        return INPUT_FULL;

    // Since user input a character, previous attempt at quiting is reset
    input->backOnce = false;

    // Input not full
    input->data[input->index] = key - '0';
    input->index = input->index + 1;

    return INPUT_OK;
}
void keypad_getResponse(char key, menu_e mNum, pendingResponse_s *r)
{
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
        // Hnadled else where
        break;
    case DISPENSING_WATER:
        // no action
        break;
    case DISPLAY_NEW_QUEUE_NUM:
        // no action
        break;
    case NOTIFY_INVALID_INPUT:
        // no action
        break;
    case NOTIFY_QUEUE_FULL:
        // no action
        break;
    }
}