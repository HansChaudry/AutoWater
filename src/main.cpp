#include <Arduino.h>
#include <PumpState.h>

// put function declarations here:
const int pumpPin = 7;
PumpState pumpState;
WaterLevel waterLevel;
void startPump();
void stopPump();
void SetWaterLevel();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pumpPin, OUTPUT);
  pumpState = Ready;
  SetWaterLevel();
}

void loop() {
  // put your main code here, to run repeatedly:
  int val;
  val=analogRead(0);     // sensor Aout pin connected to A0 pin of Ardiuno
  Serial.println(val);        // print the value in serial monitor
  
  if(val > 350){
    startPump();
  }
  else{
    stopPump();
  }

  delay(1000);
}

// put function definitions here:
void startPump() {
  if(waterLevel != Empty){
    digitalWrite(pumpPin, HIGH);
    pumpState = Busy;
  }
  SetWaterLevel();
}

void stopPump(){
  digitalWrite(pumpPin, LOW);
  pumpState = Ready;
  SetWaterLevel();
}

void SetWaterLevel(){
  //TODO: check and set water level
  return;
}