#ifndef FluorescentEffect_H
#define FluorescentEffect_H

#include "Arduino.h"

class FluorescentEffect{
   private:
      int ledPin; // connected pin
      unsigned long previousMillis;
      bool flickering;
      int step;
      bool activated;
      
      public:
      FluorescentEffect(int pin);   // Constructor
      void Update();                // Method to animate the TL
      void Toggle(bool new_state);  // Method to Toggle the TL
         


    };
#endif