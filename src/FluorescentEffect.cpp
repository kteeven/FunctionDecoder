#include "FluorescentEffect_class.h"

FluorescentEffect::FluorescentEffect(int pin) {
    ledPin = pin;
   // flickering = true;
    step = 0;
    previousMillis = 0;
    pinMode(ledPin, OUTPUT);
    
    
    //_pin = pin;
   // pinMode(_pin, OUTPUT);  // Set pin as output
}

void FluorescentEffect::Update() {
    if(activated == 0){
      digitalWrite(ledPin, LOW);
    }
  else if (flickering) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= random(100, 500)) {
            previousMillis = currentMillis;
            step++;

            if (step % 2 == 0) {
                digitalWrite(ledPin, HIGH);
            } else {
                digitalWrite(ledPin, LOW);
            }

            if (step > 10) {
                flickering = false;
                digitalWrite(ledPin, HIGH);
            }
        }
       // digitalWrite(ledPin, HIGH);
    }
}

void FluorescentEffect::Toggle(bool new_state){
 if(new_state == 1){
  activated = 1;
  flickering = 1;
  step = 0;
  Serial.println("TL light on");
  Serial.print("Pin Number");
  Serial.println(ledPin);
 }
 else{
  activated = 0;
  flickering = 0;
  Serial.println("TL light off");
 }
  
}




