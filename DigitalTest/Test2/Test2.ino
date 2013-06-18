// Pin definitions
const int knockSensor1 = 51; 
const int knockSensor2 = 52; 
const int knockSensor3 = 53;         // Piezo sensor on pin 0.

int knockSensorValue1 = 0;
int knockSensorValue2 = 0;
int knockSensorValue3 = 0;
int start = 0;
int currentTime = 0;
int reach1 = 0;
int reach2 = 0;
int reach3 = 0;



void setup() {
  Serial.begin(9600);               			// Uncomment the Serial.bla lines for debugging.
  Serial.println("Program start.");
  start = micros();  			// but feel free to comment them out after it's working right.

}

void loop() {
  // Listen for any knock at all.

  currentTime = micros();

  while(true) {
  knockSensorValue1 = digitalRead(knockSensor1);
  if(knockSensorValue1!=0) {
  	Serial.println("1");
  	reach1=micros();
  	break;
	}
  }
  while(true) {
  knockSensorValue2 = digitalRead(knockSensor2);
  if(knockSensorValue2!=0) {
  	Serial.println("2");
  	reach2=micros();
  	break;
	}
  }
  while(true) {
  knockSensorValue3 = digitalRead(knockSensor3);
  if(knockSensorValue3!=0) {
  	Serial.println("3");
  	reach3=micros();
  	break;
	}
  }
  	Serial.println(String(reach2 - reach1));
  	Serial.println(String(reach3 - reach2));
  }

