#include <Arduino.h>
#include <PumpState.h>

// put function declarations here:
int pumpPin = 7;
PumpState pumpState;
void startPump();
void stopPump();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pumpPin, OUTPUT);
  pumpState = Ready;
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
  if(!pumpState){
    digitalWrite(pumpPin, HIGH);
    pumpState = Busy;
  }

  //TODO: check water level. If the level is too low stop the pump. and set pump state to empty

}

void stopPump(){
  digitalWrite(pumpPin, LOW);
  pumpState = Ready;
}