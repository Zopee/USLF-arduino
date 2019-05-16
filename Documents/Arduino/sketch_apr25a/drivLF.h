#ifndef(drivLF.h)
#define(drivLF.h)

#include "Arduino.h"

Class driv {

public:

driv(float LD, float RD, int trigPinL, int trigPinR, int echoPinL, int echoPinR){

  void drividy(float LD, float RD);

  float LD2,RD2;

  LD2 = LD;
  RD2 = RD;
  
private:





}
