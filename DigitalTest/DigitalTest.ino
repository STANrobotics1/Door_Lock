#include <digitalWriteFast.h>

// Pin definitions
const int knockSensor1 = 51; 
const int knockSensor2 = 52; 
const int knockSensor3 = 53;         // Piezo sensor on pin 0.

int knockSensorValue1 = 0;
int knockSensorValue2 = 0;
int knockSensorValue3 = 0;
int start = 0;
int reach1 = 0;
int reach2 = 0;
int reach3 = 0;
String endPrint = "";



void setup() {
  Serial.begin(9600);                     // Uncomment the Serial.bla lines for debugging.
  Serial.println("Program start.");
  start = micros();       // but feel free to comment them out after it's working right.

}

void loop() {
  // Listen for any knock at all.

  while(true) {
  knockSensorValue1 = digitalReadFast(knockSensor1);
    if(knockSensorValue1!=0) {
      endprint += "1\n";
      reach1=micros();
      break;
    }
  }
  while(true) {
  knockSensorValue2 = digitalReadFast(knockSensor2);
    if(knockSensorValue2!=0) {
      endprint += "2\n";
      reach2=micros();
      break;
    }
  }
  while(true) {
  knockSensorValue3 = digitalReadFast(knockSensor3);
    if(knockSensorValue3!=0) {
      endprint += "3\n";
      reach3=micros();
      break;
    }
  }

  Serial.print(endPrint);
  delay(10);
  Serial.println(String(reach2 - reach1));
  delay(10);
  Serial.println(String(reach3 - reach2));
  delay(10);
  endPrint = "";
}

