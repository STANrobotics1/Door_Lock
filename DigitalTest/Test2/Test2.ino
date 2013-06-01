// Pin definitions
const int knockSensor = 52;         // Piezo sensor on pin 0.

int knockSensorValue = 0;


void setup() {
  Serial.begin(9600);               			// Uncomment the Serial.bla lines for debugging.
  Serial.println("Program start.");  			// but feel free to comment them out after it's working right.

}

void loop() {
  // Listen for any knock at all.
  knockSensorValue = digitalRead(knockSensor);
  Serial.println(knockSensorValue);
}
