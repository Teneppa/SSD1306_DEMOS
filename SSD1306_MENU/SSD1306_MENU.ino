/*
 * Testcode for displaying a list/menu
 * and selecting something from the list.
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

// These are used for the drawing routines, somehow using
// SCREEN_WIDTH-1 didn't work and this works (I have no idea why),
// so yeah...
const uint8_t screenW = SCREEN_WIDTH - 1;
const uint8_t screenH = SCREEN_HEIGHT - 1;

// This is the list
uint8_t list_size = 5;
String list[list_size] = {"YT", "404", "512", "1024", "2048"};

// DANG SON this is the best library EVER AND I JUST DISCOVERED IT LOL :D
// It's used to detect if the buttons were PRESSED once
#include <Bounce2.h>
Bounce bdown = Bounce();
Bounce bup = Bounce();

// This is executed only once
void setup() {

  // Attach pins 2 and 3 to the debounce objects
  bdown.attach(2, INPUT_PULLUP);
  bup.attach(3, INPUT_PULLUP);

  // Make the screen alive
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setRotation(2);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
}

// The index of the selection on the list
uint8_t index = 0;
void loop() {
  // Update the buttons debouncing routine
  bdown.update();
  bup.update();

  // Clear the screen
  display.clearDisplay();

  // Draw the menu
  displayMenu(list, list_size, index);

  // If you press the down -button and the index is bigger than zero, decrease
  // the index value
  if(bdown.fell()) {
    if(index>0) {
      index--;
    }
  }

  // If you press the up -button and the index is smaller than (<list_size>-1), increase
  // the index value
  if(bup.fell()) {
    if(index<list_size-1) {
      index++;
    }
  }

  // This will push the display buffer to the display so we can look
  // at it
  display.display();
}

// Dis draws the menu
void displayMenu(String listOfItems[], uint8_t len, uint8_t index) {
  display.drawRect(0, 0, screenW, screenH, 1);

  // Draw the elements (text)
  for (uint8_t i = 0; i < len; i++) {

    // If the text that we are drawing is the selected, draw the text
    // in inverse colors
    if (i == index) {
      display.setTextColor(BLACK, WHITE);
    } else {
      display.setTextColor(WHITE);
    }

    // Set the cursor to the correct position and yeet the text
    // to the display buffer
    display.setCursor(4, 4 + i * (screenH / len));
    display.print(listOfItems[i]);
  }

  // Draw the separating lines
  // We need only n-1 lines, so len-1
  for (uint8_t i = 0; i < len - 1; i++) {
    // We want to draw them equally spaced, and we don't need one at y=0,
    // so (i+1)*(display_height/itemCount) returns the height for the line
    uint8_t ly = (i + 1) * (screenH / (len));
    display.drawLine(0, ly, screenW, ly, 1);
  }
}