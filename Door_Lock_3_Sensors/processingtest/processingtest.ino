/* Detects patterns of knocks and triggers a motor to unlock
it if the pattern is correct.
By Steve Hoefer http://grathio.com
Version 0.1.10.20.10
Licensed under Creative Commons Attribution-Noncommercial-Share Alike 3.0
http://creativecommons.org/licenses/by-nc-sa/3.0/us/
(In short: Do what you want, just be sure to include this line and the four above it, and don't sell it or use it in anything you sell without contacting me.)
Analog Pin 0: Piezo speaker (connected to ground with 1M pulldown resistor)
Digital Pin 2: Switch to enter a new code. Short this to enter programming mode.
Digital Pin 3: DC gear reduction motor attached to the lock. (Or a motor controller or a solenoid or other unlocking mechanisim.)
Digital Pin 4: Red LED.
Digital Pin 5: Green LED.
Update: Nov 09 09: Fixed red/green LED error in the comments. Code is unchanged.
Update: Nov 20 09: Updated handling of programming button to make it more intuitive, give better feedback.
Update: Jan 20 10: Removed the "pinMode(knockSensor, OUTPUT);" line since it makes no sense and doesn't do anything.
*/
 
// Pin definitions
const int knockSensor1 = 0; // Piezo sensor on pin 0.
const int knockSensor2 = 1; // Piezo sensor on pin 1.
const int knockSensor3 = 2; // Piezo sensor on pin 2.
const int programSwitch = 2; // If this is high we program a new code.
const int lockMotor = 3; // Gear motor used to turn the lock.
const int redLED = 4; // Status LED
const int greenLED = 5; // Status LED
 
// Tuning constants. Could be made vars and hoooked to potentiometers for soft configuration, etc.
const int threshold1 = 2;
const int threshold2 = 2;
const int threshold3 = 2; // Minimum signal from the piezo to register as a knock
const int rejectValue = 20; // If an individual knock is off by this percentage of a knock we don't unlock..
const int averageRejectValue = 15; // If the average timing of the knocks is off by this percent we don't unlock.
const int knockFadeTime = 150; // milliseconds we allow a knock to fade before we listen for another one. (Debounce timer.)
const int lockTurnTime = 650; // milliseconds that we run the motor to get it to go a half turn.

const int maximumKnocks = 30; // Maximum number of knocks to listen for.
const int knockComplete = 1200; // Longest time to wait for a knock before we assume that it's finished.


// Variables.
int secretCode[maximumKnocks] = {50, 25, 25, 50, 100, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Initial setup: "Shave and a Hair Cut, two bits."
int knockReading1[maximumKnocks];
int knockReading2[maximumKnocks];
int knockReading3[maximumKnocks]; // 3 arrays of knocks, 1 for each sensor.
int knockSensorValue1 = 0;
int knockSensorValue2 = 0;
int knockSensorValue3 = 0; // Last reading of the knock sensor.
int programButtonPressed = false; // Flag so we remember the programming button setting at the end of the cycle.

void setup() {
  pinMode(lockMotor, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(programSwitch, INPUT);
  
  Serial.begin(9600); // Uncomment the Serial.bla lines for debugging.
  Serial.println("Program start."); // but feel free to comment them out after it's working right.
  
  digitalWrite(greenLED, HIGH); // Green LED on, everything is go.
}

void loop() {
  // Listen for any knock at all.
    knockSensorValue2 = analogRead(knockSensor2);
    knockSensorValue1 = analogRead(knockSensor1);
//    knockSensorValue3 = analogRead(knockSensor3);
  

  
  if (digitalRead(programSwitch)==HIGH){ // is the program button pressed?
    programButtonPressed = true; // Yes, so lets save that state
    digitalWrite(redLED, HIGH); // and turn on the red light too so we know we're programming.
  } else {
    programButtonPressed = false;
    digitalWrite(redLED, LOW);
  }
  
  if (knockSensorValue1 >=threshold1 || knockSensorValue2 >= threshold2 || knockSensorValue3 >= threshold3){
    listenToSecretKnock();
  }
  
}

// Records the timing of knocks.
void listenToSecretKnock(){
  Serial.println("knock starting");

  int i = 0;
  // First lets reset the listening array.
  for (i=0;i<maximumKnocks;i++){
    knockReading1[i]=0;
    knockReading2[i]=0;
    knockReading3[i]=0;
  }
  
  int currentKnockNumber1=0;
  int currentKnockNumber2=0;
  int currentKnockNumber3=0; // Incrementer for the array.
  int startTime=millis(); // Reference for when this knock started.
  int now=millis();
  
  digitalWrite(greenLED, LOW); // we blink the LED for a bit as a visual indicator of the knock.
  if (programButtonPressed==true){
     digitalWrite(redLED, LOW); // and the red one too if we're programming a new knock.
  }
  delay(knockFadeTime); // wait for this peak to fade before we listen to the next one.
  digitalWrite(greenLED, HIGH);
  if (programButtonPressed==true){
     digitalWrite(redLED, HIGH);
  }
  do {
    //listen for the next knock or wait for it to timeout.
        knockSensorValue2 = analogRead(knockSensor2);
    knockSensorValue1 = analogRead(knockSensor1);

//    knockSensorValue3 = analogRead(knockSensor3);
    
  // Ever iteration updates each sensor individually
  
       // SENSOR 2
    if (knockSensorValue2 >=threshold2){ //got another knock...
      //record the delay time.
      Serial.println("knock on 2nd sensor");
      now=millis();
      knockReading2[currentKnockNumber2] = now-startTime;
      currentKnockNumber2 ++;
      startTime=now;
      // and reset our timer for the next knock
      digitalWrite(greenLED, LOW);
      if (programButtonPressed==true){
        digitalWrite(redLED, LOW); // and the red one too if we're programming a new knock.
      }
      delay(knockFadeTime); // again, a little delay to let the knock decay.
      digitalWrite(greenLED, HIGH);
      if (programButtonPressed==true){
        digitalWrite(redLED, HIGH);
      }
    }
    
  // SENSOR 1
    if (knockSensorValue1 >=threshold1){ //got another knock...
      //record the delay time.
      Serial.println("knock on 1st sensor");
      now=millis();
      knockReading1[currentKnockNumber1] = now-startTime;
      currentKnockNumber1 ++; //increment the counter
      startTime=now;
      // and reset our timer for the next knock
      digitalWrite(greenLED, LOW);
      if (programButtonPressed==true){
        digitalWrite(redLED, LOW); // and the red one too if we're programming a new knock.
      }
      delay(knockFadeTime); // again, a little delay to let the knock decay.
      digitalWrite(greenLED, HIGH);
      if (programButtonPressed==true){
        digitalWrite(redLED, HIGH);
      }
    }
      

      
     // SENSOR 3
    if (knockSensorValue3 >=threshold3){ //got another knock...
      //record the delay time.
      Serial.println("knock on 3rd sensor");
      now=millis();
      knockReading3[currentKnockNumber3] = now-startTime;
      currentKnockNumber3 ++;
      startTime=now;
      // and reset our timer for the next knock
      digitalWrite(greenLED, LOW);
      if (programButtonPressed==true){
        digitalWrite(redLED, LOW); // and the red one too if we're programming a new knock.
      }
      delay(knockFadeTime); // again, a little delay to let the knock decay.
      digitalWrite(greenLED, HIGH);
      if (programButtonPressed==true){
        digitalWrite(redLED, HIGH);
      }
    }

    now=millis();
    
    //did we timeout or run out of knocks?
  } while ((now-startTime < knockComplete) && (currentKnockNumber1 < maximumKnocks));
  
  //we've got our knock recorded, lets see if it's valid
  if (programButtonPressed==false){ // only if we're not in progrmaing mode.
    if (validateKnock() == true){
      triggerDoorUnlock();
    } else {
      Serial.println("Secret knock failed.");

      // Print sensor arrays
      Serial.println("First Sensor");
      Serial.print("[");
      for (int i = 0; i < maximumKnocks ; i++) {
        Serial.print(String(knockReading1[i]));
        if (i!=maximumKnocks-1) {
        Serial.print(", ");
        }
        else {
          Serial.println("]");
        }
        delay(20);
      }

      Serial.println("Second Sensor");
      Serial.print("[");
      for (int i = 0; i < maximumKnocks ; i++) {
        Serial.print(String(knockReading2[i]));
        if (i!=maximumKnocks-1) {
        Serial.print(", ");
        }
        else {
          Serial.println("]");
        }
        delay(20);
      }

      Serial.println("Third Sensor");
      Serial.print("[");
      for (int i = 0; i < maximumKnocks ; i++) {
        Serial.print(String(knockReading3[i]));
        if (i!=maximumKnocks-1) {
        Serial.print(", ");
        }
        else {
          Serial.println("]");
        }
        delay(20);
      }









      digitalWrite(greenLED, LOW); // We didn't unlock, so blink the red LED as visual feedback.
      for (i=0;i<4;i++){	
        digitalWrite(redLED, HIGH);
        delay(100);
        digitalWrite(redLED, LOW);
        delay(100);
      }
      digitalWrite(greenLED, HIGH);
    }
  } else { // if we're in programming mode we still validate the lock, we just don't do anything with the lock
    validateKnock();
    // and we blink the green and red alternately to show that program is complete.
    Serial.println("New lock stored.");
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    for (i=0;i<3;i++){
      delay(100);
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
      delay(100);
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
    }
  }
  
}

  




// Runs the motor (or whatever) to unlock the door.
void triggerDoorUnlock(){
  Serial.println("Door unlocked!");
  int i=0;
  
  // turn the motor on for a bit.
  digitalWrite(lockMotor, HIGH);
  digitalWrite(greenLED, HIGH); // And the green LED too.
  
  delay (lockTurnTime); // Wait a bit.
  
  digitalWrite(lockMotor, LOW); // Turn the motor off.
  
  // Blink the green LED a few times for more visual feedback.
  for (i=0; i < 5; i++){
      digitalWrite(greenLED, LOW);
      delay(100);
      digitalWrite(greenLED, HIGH);
      delay(100);
  }
   
}

// Sees if our knock matches the secret.
// returns true if it's a good knock, false if it's not.
// todo: break it into smaller functions for readability.
boolean validateKnock(){
  int i=0;
 
  // simplest check first: Did we get the right number of knocks?
  int currentKnockCount = 0;
  int secretKnockCount = 0;
  int maxKnockInterval = 0; // We use this later to normalize the times.
  
  for (i=0;i<maximumKnocks;i++){
    if (knockReading1[i] > 0){
      currentKnockCount++;
    }
    if (secretCode[i] > 0){ //todo: precalculate this.
      secretKnockCount++;
    }
    
    if (knockReading1[i] > maxKnockInterval){ // collect normalization data while we're looping.
      maxKnockInterval = knockReading1[i];
    }
  }
  
  // If we're recording a new knock, save the info and get out of here.
  if (programButtonPressed==true){
      for (i=0;i<maximumKnocks;i++){ // normalize the times
        secretCode[i]= map(knockReading1[i],0, maxKnockInterval, 0, 100);
      }
      // And flash the lights in the recorded pattern to let us know it's been programmed.
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, LOW);
      delay(1000);
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, HIGH);
      delay(50);
      for (i = 0; i < maximumKnocks ; i++){
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, LOW);
        // only turn it on if there's a delay
        if (secretCode[i] > 0){
          delay( map(secretCode[i],0, 100, 0, maxKnockInterval)); // Expand the time back out to what it was. Roughly.
          digitalWrite(greenLED, HIGH);
          digitalWrite(redLED, HIGH);
        }
        delay(50);
      }
return false; // We don't unlock the door when we are recording a new knock.
  }
  
  if (currentKnockCount != secretKnockCount){
    return false;
  }
  
  /* Now we compare the relative intervals of our knocks, not the absolute time between them.
(ie: if you do the same pattern slow or fast it should still open the door.)
This makes it less picky, which while making it less secure can also make it
less of a pain to use if you're tempo is a little slow or fast.
*/
  int totaltimeDifferences=0;
  int timeDiff=0;
  for (i=0;i<maximumKnocks;i++){ // Normalize the times
    knockReading1[i]= map(knockReading1[i],0, maxKnockInterval, 0, 100);
    knockReading2[i]= map(knockReading2[i],0, maxKnockInterval, 0, 100);
    knockReading3[i]= map(knockReading3[i],0, maxKnockInterval, 0, 100);
    timeDiff = abs(knockReading1[i]-secretCode[i]);
    if (timeDiff > rejectValue){ // Individual value too far out of whack
      return false;
    }
    totaltimeDifferences += timeDiff;
  }
  // It can also fail if the whole thing is too inaccurate.
  if (totaltimeDifferences/secretKnockCount>averageRejectValue){
    return false;
  }
  
  return true;
  
}
