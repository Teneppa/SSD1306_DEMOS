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

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setRotation(0);
  //display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
}

void loop() {
  uint16_t dTime = 150;
  display.clearDisplay();

  display.drawTriangle(21,0,32,0,32,11,1);
  delay(dTime);
  display.display();
  
  display.drawTriangle(95,0,95,11,106,0,1);
  delay(dTime);
  display.display();
  
  display.drawRect(56,20,15,44,1);
  delay(dTime);
  display.display();

  display.drawRect(26,49,3,15,1);
  delay(dTime);
  display.display();
  display.drawRect(99,49,3,15,1);
  delay(dTime);
  display.display();
  
  display.drawLine(99,49,127,21,1);
  delay(dTime);
  display.display();
  display.drawLine(100,49,127,22,1);
  delay(dTime);
  display.display();
  display.drawLine(101,49,127,23,1);
  delay(dTime);
  display.display();
  
  display.drawLine(26,49,0,23,1);
  delay(dTime);
  display.display();
  display.drawLine(27,49,0,22,1);
  delay(dTime);
  display.display();
  display.drawLine(28,49,0,21,1);
  delay(dTime);
  display.display();

  // Fill T
  display.drawRect(33,0,62,13,1);
  delay(dTime);
  display.display();

  display.drawTriangle(0,63,0,56,7,63,1);
  delay(dTime);
  display.display();
  display.drawTriangle(120,63,127,56,127,63,1);
  delay(dTime);
  display.display();
  
  display.display();
}