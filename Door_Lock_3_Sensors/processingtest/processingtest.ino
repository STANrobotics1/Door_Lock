// Will print arrays of 3 sensor's data
#include <digitalWriteFast.h>
// Pin definitions
const int knockSensor1 = 51; // Piezo sensor 1.
const int knockSensor2 = 52; // Piezo sensor 2.
const int knockSensor3 = 53; // Piezo sensor 3.
const int programSwitch = 2; // If this is high we program a new code.
const int lockMotor = 3; // Gear motor used to turn the lock.
const int redLED = 4; // Status LED
const int greenLED = 5; // Status LED
 

const int rejectValue = 20; // If an individual knock is off by this percentage of a knock we don't unlock..
const int averageRejectValue = 15; // If the average timing of the knocks is off by this percent we don't unlock.
const int knockFadeTime = 150; // milliseconds we allow a knock to fade before we listen for another one. (Debounce timer.)
const int lockTurnTime = 650; // milliseconds that we run the motor to get it to go a half turn.

const int maximumKnocks = 20; // Maximum number of knocks to listen for.
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
  pinMode(knockSensor1, INPUT);
  pinMode(knockSensor2, INPUT);
  pinMode(knockSensor3, INPUT);
  
  Serial.begin(9600); // Uncomment the Serial.bla lines for debugging.
  Serial.println("Program start."); // but feel free to comment them out after it's working right.
  
  digitalWrite(greenLED, HIGH); // Green LED on, everything is go.
}

void loop() {
  if (digitalRead(programSwitch)==HIGH){ // is the program button pressed?
    programButtonPressed = true; // Yes, so lets save that state
    digitalWrite(redLED, HIGH); // and turn on the red light too so we know we're programming.
  } else {
    programButtonPressed = false;
    digitalWrite(redLED, LOW);
  }
  
  listenToSecretKnock();  
}

// Records the timing of knocks.
void listenToSecretKnock(){

  int i = 0;
  // First lets reset the listening array.
  for (i=0;i<maximumKnocks;i++){
    knockReading1[i]=0;
    knockReading2[i]=0;
    knockReading3[i]=0;
  }
  
  int currentKnockNumber = 0;// Incrementer for the array.
  int startTime=micros(); // Reference for when this knock started.
  int now=micros(); // initialize time of first knock (will change with every knock)
  
  digitalWrite(greenLED, LOW); // we blink the LED for a bit as a visual indicator of the knock.
  if (programButtonPressed==true){
     digitalWrite(redLED, LOW); // and the red one too if we're programming a new knock.
  }
  digitalWrite(greenLED, HIGH);
  if (programButtonPressed==true){
     digitalWrite(redLED, HIGH);
  }


    while(true) {

      knockSensorValue1 = digitalReadFast(knockSensor1);
      knockSensorValue2 = digitalReadFast(knockSensor2);
      knockSensorValue3 = digitalReadFast(knockSensor3);

    if(knockSensorValue1 == 1) {
      Serial.println("knock starting");
      now = micros();   // Reference time of initial knock
      checkSensor1();   // Waits for 2 remaining sensors to complete

      /* All checkSensor functions should include all now = micros()
      commands and knockReading[1] and so on so that each adds 1 
      entry to each of 3 sensor arrays. */



      startTime = now; // Reference the end of a knock
      delay(knockFadeTime);  // Wait for knock's reverberations to end
      currentKnockNumber ++;
      break;
    }
    else if(knockSensorValue2 == 1) {
      Serial.println("knock starting");
      now = micros();    // Reference time of initial knock
      checkSensor2();    // Waits for 2 remaining sensors to complete

      startTime = now;   // Reference the end of a knock
      delay(knockFadeTime);  // Wait for knock's reverberations to end
      currentKnockNumber ++;
      break;
    }
    else if(knockSensorValue3 == 1) {
      Serial.println("knock starting");
      now = micros();   // Reference time of initial knock
      checkSensor3();   // Waits for 2 remaining sensors to complete

      startTime = now;   // Reference the end of a knock
      delay(knockFadeTime);  // Wait for knock's reverberations to end
      currentKnockNumber ++;
      break;
    }


  }
    
    
  // Need to implement while loop format from digitaltest2
  // After final while loop completes, we can do the delay(knockFadeTime)
  // Otherwise, the loop should time out and execute the regular
  // invalid knock sequence.

  // Make special note of startTime = now, this should probably be
  // included with the final sensor to be reached, since you 
  // only want to know the time from the last knock's completion.

  do {
  // SENSOR 1
    if (knockSensorValue1 == 1){ //got another knock...
      //record the delay time.
      Serial.println("knock on 1st sensor");
      now=micros();
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
      
       // SENSOR 2
    if (knockSensorValue2 == 1){ //got another knock...
      //record the delay time.
      Serial.println("knock on 2nd sensor");
      now=micros();
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
      
     // SENSOR 3
    if (knockSensorValue3 == 1){ //got another knock...
      //record the delay time.
      Serial.println("knock on 3rd sensor");
      now=micros();
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
