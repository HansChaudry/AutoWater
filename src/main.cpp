#include <Arduino.h>

// put function declarations here:
int pumpPin = 7;
bool pumpState = false;
void startPump();
void stopPump();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val;
  val=analogRead(0);     // sensor Aout pin connected to A0 pin of Ardiuno
  Serial.println(val);        // print the value in serial monitor
  if(val > 400){
    if (!pumpState)
    {
      startPump();
    }
  }
  
  if(val < 400){
    if(pumpState){
      stopPump();
    }
  }
  delay(1000);
}

// put function definitions here:
void startPump() {
  digitalWrite(pumpPin, HIGH);
  pumpState = true;
}

void stopPump(){
  digitalWrite(pumpPin, LOW);
  pumpState = false;
}