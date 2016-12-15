#include "ReadAnalog.h"

double ReadAnalog::getTemp(){
  float reading = analogRead(mPin);
  return (5.0 * reading * 100.0) / 1024;
}

double ReadAnalog::readShake(){
  return analogRead(mPin);
}
