#include <digitalWriteFast.h>

// Allows for any ordering of incoming knocks. Doesn't force ordering.

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
boolean sequenceCompleted = false;



void setup() {
  Serial.begin(9600);                     // Uncomment the Serial.bla lines for debugging.
  Serial.println("Program start.");
  start = micros();       // but feel free to comment them out after it's working right.

}

void loop() {

  
  // Listen for any knock at all.

  while(true) {
  knockSensorValue1 = digitalReadFast(knockSensor1);
  knockSensorValue2 = digitalReadFast(knockSensor2);
  knockSensorValue3 = digitalReadFast(knockSensor3);
    if(knockSensorValue1!=0) {
      checkSensor1();
      break;
    }
    if(knockSensorValue2!=0) {
      checkSensor2();
      break;
    }
    if(knockSensorValue3!=0) {
      checkSensor3();
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
  sequenceCompleted = false;
  
}

void checkSensor1() {
  endprint += "1\n";
  reach1=micros();
  while (true) {
    // waits for either of the other two sensors to get the knock
    knockSensorValue2 = digitalReadFast(knockSensor2);
    knockSensorValue3 = digitalReadFast(knockSensor3);
    // conditions for if sensor 2 is first
    if(knockSensorValue2!=0) {
      endprint += "2\n";
      reach2=micros();
      // waits for the final sensor to receive knock
      while (true) {
        knockSensorValue3 = digitalReadFast(knockSensor3);
        if(knockSensorValue3!=0) {
          endprint += "3\n";
          reach3=micros();
          sequenceCompleted = true;
          break;
        }
      }
    }
    // conditions for if sensor 3 is first
    if(knockSensorValue3!=0) {
      endprint += "3\n";
      reach3=micros();
      // waits for the final sensor to receive knock 
      while (true) {
        knockSensorValue2 = digitalReadFast(knockSensor2);
        if(knockSensorValue2!=0) {
          endprint += "2\n";
          reach2=micros();
          sequenceCompleted = true;
          break;
        }
      }
    }
    // need two breaks to exit loop
    if(sequenceCompleted) break;
  }  
}

void checkSensor2() {
  endprint += "2\n";
  reach2=micros();
  while (true) {
    knockSensorValue1 = digitalReadFast(knockSensor1);
    knockSensorValue3 = digitalReadFast(knockSensor3);
    if(knockSensorValue1!=0) {
      endprint += "1\n";
      reach1=micros();
      while (true) {
        knockSensorValue3 = digitalReadFast(knockSensor3);
        if(knockSensorValue3!=0) {
          endprint += "3\n";
          reach3=micros();
          sequenceCompleted = true;
          break;
        }
      }
    }
    if(knockSensorValue3!=0) {
      endprint += "3\n";
      reach3=micros();
      while (true) {
        knockSensorValue1 = digitalReadFast(knockSensor1);
        if(knockSensorValue1!=0) {
          endprint += "1\n";
          reach1=micros();
          sequenceCompleted = true;
          break;
        }
      }
    }
    if(sequenceCompleted) break;
  }  
}

void checkSensor3() {
  endprint += "3\n";
  reach3=micros();
  while (true) {
    knockSensorValue1 = digitalReadFast(knockSensor1);
    knockSensorValue2 = digitalReadFast(knockSensor2);
    if(knockSensorValue1!=0) {
      endprint += "1\n";
      reach1=micros();
      while (true) {
        knockSensorValue2 = digitalReadFast(knockSensor2);
        if(knockSensorValue2!=0) {
          endprint += "2\n";
          reach2=micros();
          sequenceCompleted = true;
          break;
        }
      }
    }
    if(knockSensorValue2!=0) {
      endprint += "2\n";
      reach2=micros();
      while (true) {
        knockSensorValue1 = digitalReadFast(knockSensor1);
        if(knockSensorValue1!=0) {
          endprint += "1\n";
          reach1=micros();
          sequenceCompleted = true;
          break;
        }
      }
    }
    if(sequenceCompleted) break;
  }  
}

