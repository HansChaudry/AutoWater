#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define I2C_ADDRESS 0x3C

// Pin Definitions
const int PUMP_CONTROL_PIN = 7;
const int MOISTURE_SENSOR_PIN = 0;
const int WATER_LEVEL_SENSOR_PIN = 3;

// Thresholds and Constants
const int MOISTURE_THRESHOLD = 350;

// Enum Definitions
enum PumpState { Ready, Busy };
enum WaterLevel { Empty, Low, Full };

// Variables
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
PumpState pumpState = Ready;
WaterLevel waterLevel = Empty;
int moistureLevel = 0;

// Function Prototypes
void setupPump();
void setupDisplay();
void readMoisture();
void controlPump();
void updateDisplay();
void checkWaterLevel();

void setup() {
    Serial.begin(9600);
    setupPump();
    setupDisplay();
}

void loop() {
    readMoisture();
    checkWaterLevel();
    controlPump();
    updateDisplay();
    delay(1000);
}

void setupPump() {
    pinMode(PUMP_CONTROL_PIN, OUTPUT);
    pumpState = Ready;
}

void setupDisplay() {
    if (!display.begin(I2C_ADDRESS)) {
        Serial.println("Display initialization failed!");
        while (1); // Halt
    }
    display.display();
    delay(2000);
}

void readMoisture() {
    moistureLevel = analogRead(MOISTURE_SENSOR_PIN);
}

void checkWaterLevel() {
    int sensorValue = analogRead(WATER_LEVEL_SENSOR_PIN);
    // Placeholder logic
    if (sensorValue < 100) waterLevel = Empty;
    else if (sensorValue < 300) waterLevel = Low;
    else waterLevel = Full;
}

void controlPump() {
    if (moistureLevel > MOISTURE_THRESHOLD && waterLevel != Empty) {
        digitalWrite(PUMP_CONTROL_PIN, HIGH);
        pumpState = Busy;
    } else {
        digitalWrite(PUMP_CONTROL_PIN, LOW);
        pumpState = Ready;
    }
}

void updateDisplay() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(10, 10);
    display.println(moistureLevel);

    display.setTextSize(1);
    display.setCursor(10, 40);
    if (moistureLevel > MOISTURE_THRESHOLD) {
        display.println("Needs Water!");
    } else {
        display.println("Happy Plant :)");
    }

    display.display();
}
