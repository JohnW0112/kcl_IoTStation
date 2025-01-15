#include <Arduino.h>
#include "oled.h" 
#include "pump.h"
#include "sonic.h"
#include "queue.h"

/*define*/

/*variables*/

queue_s q;
menu_e menuNumber;

void display_init(){
  Adafruit_SSD1306 display;
  display = Adafruit_SSD1306(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, &Wire, OLED_RESET);
  menuNumber = MAIN_MENU;

}

void setup() {
  Serial.begin(115200);

  display_init();

}

void loop() {
  
}
