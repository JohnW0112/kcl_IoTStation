#include "oled.h"

/*static functions*/
static void oled_displayMainMenu(Adafruit_SSD1306 *display)
{
    display->clearDisplay();

    // display water level text
    display->setCursor(OLED_WATER_LEVEL_TAG_CURSOR);
    display->println("Water Level:");

    // display queue status
    display->setCursor(OLED_QUEUE_STATUS_TAG_CURSOR);
    display->println("Queue number:");

    // display options
    display->setCursor(OLED_GET_WATER_CURSOR);
    display->println("Press 1 for water");

    display->setCursor(OLED_GET_TICKET_CURSOR);
    display->println("Press 2 to get queue number");

    display->display();
}

static void oled_displayWantedWater(Adafruit_SSD1306 *display)
{
    // TODO: Display user input
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

static void oled_displayQueueNum(Adafruit_SSD1306 *display)
{
    // TODO: Display new queue number to user
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

void oled_updateQueue(Adafruit_SSD1306 *display, water_level_e level)
{
    // TODO: Update current queue number in main menu
}

void oled_display(Adafruit_SSD1306 *display, menu_e mNum)
{
    switch (mNum)
    {
    case MAIN_MENU:
        oled_displayMainMenu(display);
        break;
    case WANTED_WATER:
        oled_displayWantedWater(display);
        break;
    case DISPENSING_WATER:
        oled_displayPumping(display);
        break;
    case DISPLAY_QUEUE_NUM:
        oled_displayQueueNum(display);
        break;
    }
}
