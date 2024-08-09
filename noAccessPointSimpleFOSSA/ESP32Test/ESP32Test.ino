#define USER_SETUP_LOADED // Prevents loading the default User_Setup.h

#define ST7796_DRIVER

#define TFT_WIDTH  320
#define TFT_HEIGHT 480

#define TFT_MISO -1
#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   16
#define TFT_RST  23
#define TFT_BL   4   // LED backlight control pin

#define TOUCH_CS 14    // Chip select pin (T_CS) of touch screen

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT

#define SPI_FREQUENCY  27000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  delay(1000);  // Small delay to stabilize serial communication
  Serial.println("Initializing TFT...");

  pinMode(TFT_BL, OUTPUT);  // Set the backlight pin as an output
  digitalWrite(TFT_BL, HIGH);  // Turn on the backlight

  tft.init();  // Initialize the TFT screen
  tft.setRotation(1);  // Set the screen rotation
  tft.fillScreen(TFT_RED);  // Set background color to red

  tft.setTextColor(TFT_WHITE);  // Set text color to white
  tft.setTextSize(2);  // Set text size
  tft.setCursor(10, 10);  // Set cursor position
  tft.println("TFT Screen Test");  // Print test message

  Serial.println("TFT initialized and background color set");
  Serial.println("TFT Screen Test Displayed");
}

void loop() {
  // Empty loop
}
