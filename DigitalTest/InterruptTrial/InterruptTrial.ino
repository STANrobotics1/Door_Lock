// Forces a 1-2-3 knocking pattern and prints time intervals between sensors.
// This code uses the method of interrupts, instead of the while loop structure.

// Pins
const int knockSensor1 = 2; 
const int knockSensor2 = 3; 
const int knockSensor3 = 21;         

int knockSensorValue1 = 0;
int knockSensorValue2 = 0;
int knockSensorValue3 = 0;

int start = 0;

int reach1 = 0;
int reach2 = 0;
int reach3 = 0;

String toPrint = "";

void setup() {
  pinMode(knockSensor1, INPUT);
  pinMode(knockSensor2, INPUT);
  pinMode(knockSensor3, INPUT);
  attachInterrupt(0,saveTime1,RISING);
  attachInterrupt(1,saveTime2,RISING);
  attachInterrupt(2,saveTime3,RISING);
  Serial.begin(9600);                     
  Serial.println("Program start.");
  start = micros();      

}

void loop() {
  
  if(micros() - start >= 10000000) {
     Serial.println("Serial Start : " + String(start));
     start = micros();
     Serial.print("1st : "); Serial.println(reach1);
     delay(1000);
     Serial.print("2nd : "); Serial.println(reach2);
     delay(1000);
     Serial.print("3rd : "); Serial.println(reach3);
     delay(1000);
     Serial.println("Difference = " + String(reach2 - reach1) + "  ");
     delay(1000);
     Serial.println("Difference 2 = " + String(reach3 - reach2) + " ");
     delay(1000);
     Serial.println(start); Serial.println(start  + 1);
     while(true) {
     }
       
  }
  
}


void saveTime1() {
  if(reach1 == 0) {
    reach1 = micros();    
  }
}

void saveTime2() {
  if(reach2 == 0) {
    reach2 = micros();    
  }
}

void saveTime3() {
  if(reach3 == 0) {
    reach3 = micros();    
  }
}
