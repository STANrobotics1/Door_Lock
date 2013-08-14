#include <digitalWriteFast.h>

// Pin definitions
int knockSensor1 = 2; 
int knockSensor2 = 3; 
int knockSensor3 = 21;

int knockSensorValue1 = 0;
int knockSensorValue2 = 0;
int knockSensorValue3 = 0;
int start = 0;
int reach1 = 0;
int reach2 = 0;
int reach3 = 0;
String endPrint = "";



void setup() {
  pinMode(knockSensor1, INPUT);
  pinMode(knockSensor2, INPUT);
  pinMode(knockSensor3, INPUT);
  Serial.begin(9600);                     
  Serial.println("Program start.");
  start = micros();    

}

void loop() {
  // Listen for any knock at all.


  knockSensorValue1 = digitalRead(knockSensor1);


  knockSensorValue2 = digitalRead(knockSensor2);


  knockSensorValue3 = digitalRead(knockSensor3);

  if(knockSensorValue1 == 1 ){
  Serial.println("Sensor 1 ");
  }
  if(knockSensorValue2 == 1 ){
  Serial.println("Sensor 2 " );
}
  if(knockSensorValue3 == 1 ){
  Serial.println("Sensor 3 " );
}
}

