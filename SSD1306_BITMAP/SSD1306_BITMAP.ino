/*
 * Testcode for drawing bitmaps and drawing a level with them
 *
 * You can use the bitmaps, but plz give credit if you use them in your code!
 * 
 * This crappy demo was made by
 *  > Teukkaniikka
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

// 8x8 block
const unsigned char PROGMEM block [] = {
  0xFF, 0xC3, 0x81, 0x99, 0x99, 0x81, 0xC3, 0xFF,
};

// 8x8 player
const unsigned char PROGMEM mushroom [] = {
  0x3C, 0x5A, 0x5A, 0xFF, 0x24, 0x24, 0x24, 0x66,
};

// 8x8 spike
const unsigned char PROGMEM spike [] = {
  0x18, 0x18, 0x24, 0x24, 0x24, 0x42, 0x42, 0x42,
};

// 8x8 alien (from space invaders)
const unsigned char PROGMEM alien [] = {
  0x42, 0x24, 0x7E, 0xDB, 0xFF, 0xBD, 0x24, 0x18,
};

// Which level to load?
uint8_t current_level = 0;

// How many levels do you have?
const uint8_t level_count = 1;

// This is where the levels are stored
// The level is rotated 90 degrees counter-clockwise when rendered
//
// The level 1 looks like this:
// 00000000000000
// 00000000000000
// 00000000000000
// 00000000000000
// 00000000000000
// 00000000100000
// 10000001100000
// 00010011100000
//
// And when it's rendered the outer wall is added:
// 1111111111111111
// 1000000000000001
// 1000000000000001
// 1000000000000001
// 1000000000000001
// 1000000000000001
// 1000000001000001
// 1100000011000001
// 1000100111000001
// 1111111111111111
const uint8_t m_collision_boxes[14 * level_count] = {
  //level 1
  B01000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B10000000,
  B11000000,
  B11100000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

// This is run only once
void setup() {

  // Make the screen alive
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setRotation(0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();

  // Draw all of the bitmaps diagonally
  // drawBitmap(x, y, bitmap_variable, width, height, color);
  display.drawBitmap(8, 8, mushroom, 8, 8, 1);
  display.drawBitmap(16, 16, spike, 8, 8, 1);
  display.drawBitmap(24, 24, alien, 8, 8, 1);
  display.drawBitmap(32, 32, block, 8, 8, 1);
  
  // draw the map
  drawMap();
  delay(200);

  display.display();
}

// The outer walls are always drawn without holes, and the map that you give comes inside the outer walls
void drawMap() {

  // Draw the outer wall
  for (int x = 0; x < 16; x++) {
    display.drawBitmap(x * 8, 0, block, 8, 8, 1);
    display.drawBitmap(x * 8, 56, block, 8, 8, 1);
  }
  for (int y = 1; y < 7; y++) {
    display.drawBitmap(0, y * 8, block, 8, 8, 1);
    display.drawBitmap(120, y * 8, block, 8, 8, 1);
  }

  // Draw the map
  for (int x = 1; x <= 14; x++) {
    for (int d = 1; d <= 6; d++) {
      if (m_collision_boxes[x - 1 + current_level * 14] & (1 << (7 - (d - 1)))) {
        display.drawBitmap(8 * x, 56 - (8 * d), block, 8, 8, 1);
      }
    }
  }
}