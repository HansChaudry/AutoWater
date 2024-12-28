#include <Arduino.h>
#include <unity.h>

const int PumpPin = 7;

void test_Pump(){
  pinMode(OUTPUT, PumpPin);
  digitalWrite(PumpPin, HIGH);
  delay(2000);
  digitalWrite(PumpPin,LOW);
  delay(500);
  TEST_PASS();
}

void setup(){
  UNITY_BEGIN();
  RUN_TEST(test_Pump);
  UNITY_END();

}

void loop(){
}

