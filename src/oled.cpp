#include "oled.h"

/*static functions*/
static void oled_displayMainMenu(Adafruit_SSD1306 *display, water_data_s *waterData, queue_s *q)
{
    display->clearDisplay();

    // display water level text
    display->setCursor(OLED_WATER_LEVEL_TAG_CURSOR);
    display->println("Water Level:");
    display->setCursor(OLED_WATER_LEVEL_CURSOR);
    oled_updateWaterLevel(display, waterData->currentWaterLevel);

    // display queue status
    display->setCursor(OLED_QUEUE_STATUS_TAG_CURSOR);
    display->println("Current Queue number:");
    display->setCursor(OLED_QUEUE_STATUS_CURSOR);
    if (q->isEmpty == true)
    {
        display->println("Empty queue");
    }
    else
    {
        display->println(String(q->currentQueueNumber));
    }

    // display options
    display->setCursor(OLED_GET_WATER_CURSOR);
    display->println("Press 1 for water");

    display->setCursor(OLED_GET_TICKET_CURSOR);
    display->println("Press 2 to get queue number");

    display->display();
}

static void oled_displayWantedWater(Adafruit_SSD1306 *display)
{
    display->clearDisplay();

    // display water level text
    display->setCursor(OLED_ECHO_WATER_AMOUNT_TAG_CURSOR);
    display->println("Wanted water (1-20L):");

    display->setCursor(OLED_INSTRUCTION_TAG_CURSOR);
    display->println("Press * to delete;Press # for enter");
    display->display();
}

static void oled_displayPumping(Adafruit_SSD1306 *display)
{
    display->clearDisplay();

    display->setTextSize(2);
    display->setCursor(OLED_PUMPING_CURSOR);
    display->println("PUMPING!!!");

    display->display();
    display->setTextSize(1);
}

static void oled_displayQueueNum(Adafruit_SSD1306 *display, uint16_t qNum)
{
    display->clearDisplay();

    display->setCursor(OLED_NEW_QUEUE_NUM_TAG_CURSOR);
    display->println("NEW QUEUE NUMBER:");

    display->setCursor(OLED_NEW_QUEUE_NUM_CURSOR);
    display->println(String(qNum));

    display->display();
}

static void oled_displayNotifyQueueFull(Adafruit_SSD1306 *display)
{
    display->clearDisplay();

    display->setTextSize(2);
    display->setCursor(OLED_NOTIFY_QUEUE_FULL_TAG_CURSOR);
    display->println("Queue is full!");

    display->display();
    display->setTextSize(1);
}

static void oled_displayNotifyInvalidInput(Adafruit_SSD1306 *display)
{
    display->clearDisplay();

    display->setTextSize(2);
    display->setCursor(OLED_NOTIFY_INVALID_INPUT_TAG_CURSOR);
    display->println("INVALID INPUT!");

    display->display();
    display->setTextSize(1);
}

/*public functions*/
boolean oled_init(Adafruit_SSD1306 *display)
{
    boolean displayInit = false;

    if (display->begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        displayInit = true;
        delay(500);

        display->setTextSize(1); // 6x8 pixels
        display->setTextColor(WHITE);
    }

    return displayInit;
}
void oled_echoUserInput(Adafruit_SSD1306 *display, user_input_s *input)
{
    String displayText = "";
    oled_displayWantedWater(display);

    for (uint8_t i = 0; i < 2; i++)
    {
        if (i < input->index)
        {
            displayText += String(input->data[i]);
            continue;
        }
        displayText += ' ';
    }
    Serial.println(displayText);
    display->println(displayText);

    display->display();
}

void oled_updateWaterLevel(Adafruit_SSD1306 *display, water_level_e level)
{
    display->setCursor(OLED_WATER_LEVEL_CURSOR);
    switch (level)
    {
    case WATER_HIGH:
        display->println("HIGH  ");
        break;
    case WATER_MEDIUM:
        display->println("MEDIUM");
        break;
    case WATER_LOW:
        display->println("LOW   ");
        break;
    }
    display->display();
}

void oled_updateQueue(Adafruit_SSD1306 *display, queue_s *q)
{
    display->setCursor(OLED_QUEUE_STATUS_CURSOR);
    String text = String(q->currentQueueNumber);
    display->println(text);

    display->display();
}

void oled_display(Adafruit_SSD1306 *display, menu_e mNum, queue_s *q, water_data_s *water, uint16_t displayQueueNum)
{
    switch (mNum)
    {
    case MAIN_MENU:
        oled_displayMainMenu(display, water, q);
        break;
    case WANTED_WATER:
        oled_displayWantedWater(display);
        break;
    case DISPENSING_WATER:
        oled_displayPumping(display);
        break;
    case DISPLAY_NEW_QUEUE_NUM:
        oled_displayQueueNum(display, displayQueueNum);
        break;
    case NOTIFY_QUEUE_FULL:
        oled_displayNotifyQueueFull(display);
        break;
    case NOTIFY_INVALID_INPUT:
        oled_displayNotifyInvalidInput(display);
        break;
    }
}
