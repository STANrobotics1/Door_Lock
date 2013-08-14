int Pin0 = 9; 
int Pin1 = 10; 
int Pin2 = 11; 
int Pin3 = 12; 
int fullRotation = 510;

void setup() 
{ 
 pinMode(Pin0, OUTPUT);  
 pinMode(Pin1, OUTPUT);  
 pinMode(Pin2, OUTPUT);  
 pinMode(Pin3, OUTPUT);  
} 

 void loop() 
{ 
   stepperStep(fullRotation,true);
   stepperStep(fullRotation,false);
}

void stepperStep(int num, boolean dir) {
  for(int i = 0; i < num; i++) {
    if(dir == true) {
      for(int numStep = 0; numStep <=7; numStep++) {
           switch(numStep){ 
           case 0: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, HIGH); 
           break;  
           case 1: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, HIGH); 
             digitalWrite(Pin3, HIGH); 
           break;  
           case 2: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, HIGH); 
             digitalWrite(Pin3, LOW); 
           break;  
           case 3: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, HIGH); 
             digitalWrite(Pin2, HIGH); 
             digitalWrite(Pin3, LOW); 
           break;  
           case 4: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, HIGH); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, LOW); 
           break;  
           case 5: 
             digitalWrite(Pin0, HIGH);  
             digitalWrite(Pin1, HIGH); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, LOW); 
           break;  
             case 6: 
             digitalWrite(Pin0, HIGH);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, LOW); 
           break;  
           case 7: 
             digitalWrite(Pin0, HIGH);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, HIGH); 
           break;  
           default: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, LOW); 
           break;  
         } 
         delayMicroseconds(1200);
        }
      }
      
      else if(dir == false) {
      for(int numStep = 7; numStep >= 0; numStep--) {
           switch(numStep){ 
           case 0: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, HIGH); 
           break;  
           case 1: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, HIGH); 
             digitalWrite(Pin3, HIGH); 
           break;  
           case 2: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, HIGH); 
             digitalWrite(Pin3, LOW); 
           break;  
           case 3: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, HIGH); 
             digitalWrite(Pin2, HIGH); 
             digitalWrite(Pin3, LOW); 
           break;  
           case 4: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, HIGH); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, LOW); 
           break;  
           case 5: 
             digitalWrite(Pin0, HIGH);  
             digitalWrite(Pin1, HIGH); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, LOW); 
           break;  
             case 6: 
             digitalWrite(Pin0, HIGH);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, LOW); 
           break;  
           case 7: 
             digitalWrite(Pin0, HIGH);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, HIGH); 
           break;  
           default: 
             digitalWrite(Pin0, LOW);  
             digitalWrite(Pin1, LOW); 
             digitalWrite(Pin2, LOW); 
             digitalWrite(Pin3, LOW); 
           break;  
         } 
         delayMicroseconds(1200);
      }
    }
  }
}
