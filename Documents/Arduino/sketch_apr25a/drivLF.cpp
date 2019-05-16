#include "Arduino.h"
#include "drivLF.h"

driv::driv(float LD, float RD, int trigPinL, int trigPinR, int echoPinL, int echoPinR){

  pinMode(trigPinL, OUTPUT); //trig pin is output
  pinMode(echoPinL, OUTPUT); //echo pin is output
  pinMode(trigPinR, OUTPUT); //trig pin is output
  pinMode(echoPinR, OUTPUT); //echo pin is output

  
}
