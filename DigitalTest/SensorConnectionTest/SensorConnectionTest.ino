#include <digitalWriteFast.h>

// Pin definitions
const int knockSensor1 = 11; 
const int knockSensor2 = 12; 
const int knockSensor3 = 13;

int knockSensorValue1 = 0;
int knockSensorValue2 = 0;
int knockSensorValue3 = 0;
int start = 0;
int reach1 = 0;
int reach2 = 0;
int reach3 = 0;
String endPrint = "";



void setup() {
  pinModeFast(knockSensor1, INPUT);
  pinModeFast(knockSensor2, INPUT);
  pinModeFast(knockSensor3, INPUT);
  Serial.begin(9600);                     
  Serial.println("Program start.");
  start = micros();    

}

void loop() {
  // Listen for any knock at all.


  knockSensorValue1 = digitalReadFast(knockSensor1);


  knockSensorValue2 = digitalReadFast(knockSensor2);


  knockSensorValue3 = digitalReadFast(knockSensor3);

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

