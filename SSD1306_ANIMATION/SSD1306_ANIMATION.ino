/*
   Testcode for animating a moving block,
   it doesn't do much but it moves.

   This crappy demo was made by
    > Teukkaniikka
*/

// Include all of the display drawing libraries
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// The screen resolution goes here
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

// The pinout goes here
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8

// Initialize the display object (This one is used for a display with SPI -interface!)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// These are used for the drawing routines, somehow using
// SCREEN_WIDTH-1 didn't work and this works (I have no idea why),
// so yeah...
const uint8_t screenW = SCREEN_WIDTH - 1;
const uint8_t screenH = SCREEN_HEIGHT - 1;

void setup() {
  // Make the screen alive
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setRotation(2);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
}

void loop() {
  // Clear the screen
  display.clearDisplay();

  // Fill a triangle from left to right with white (draw it)
  for (int16_t x = -40; x < screenW; x++) {
    display.fillTriangle(x, 0, x, screenH, x+40, 0, 1);
    display.display();
  }

  // Fill a triangle from left to right with black (clear the already drawn one)
  for (int16_t x = -40; x < screenW; x++) {
    display.fillTriangle(x, 0, x, screenH, x+40, 0, 0);
    display.display();
  }
  
  display.display();
}