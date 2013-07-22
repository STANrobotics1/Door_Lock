// Forces a 1-2-3 knocking pattern and prints time intervals between sensors.

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



void setup() {
  pinMode(knockSensor1, INPUT);
  pinMode(knockSensor2, INPUT);
  pinMode(knockSensor3, INPUT);
  Serial.begin(9600);                     // Uncomment the Serial.bla lines for debugging.
  Serial.println("Program start.");
  start = micros();       // but feel free to comment them out after it's working right.

}

void loop() {
  // Listen for any knock at all.

  while(true) {
  knockSensorValue1 = digitalRead(knockSensor1);
    if(knockSensorValue1!=0) {
      reach1=micros();
      break;
    }
  }
  while(true) {
  knockSensorValue2 = digitalRead(knockSensor2);
    if(knockSensorValue2!=0) {
      reach2=micros();
      break;
    }
  }
  while(true) {
  knockSensorValue3 = digitalRead(knockSensor3);
    if(knockSensorValue3!=0) {
      reach3=micros();
      break;
    }
  }
  
  

  Serial.print("1\n2\n3\n");
  Serial.println(reach2 - reach1);
  delay(10);
  Serial.println(reach3 - reach2);
  delay(10);
  
}

