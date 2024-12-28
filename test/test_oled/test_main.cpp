#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <unity.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   // QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define i2c_Address 0x3c // initialize with the I2C addr 0x3C Typically eBay OLED's

// Test: Display initialization
void test_display_initialization() {
    bool initialized = display.begin(i2c_Address);
    TEST_ASSERT_TRUE_MESSAGE(initialized, "Display initialization failed");
}


void test_draw_text() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println("Hello, OLED!");
    display.display();
    TEST_PASS();
    // Visual test; no hardware feedback available
    //TEST_PASS_MESSAGE("Text displayed successfully");
}

void setup() {
  Serial.begin(9600);

  UNITY_BEGIN();
  RUN_TEST(test_display_initialization);
  delay(2000);

  RUN_TEST(test_draw_text);
  delay(2000);
  UNITY_END();
}

void tearDown(){
    
}

void loop() {
}


