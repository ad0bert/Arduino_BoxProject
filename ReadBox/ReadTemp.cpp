#include "ReadTemp.h"

double ReadTemp::getTemp(){
  float reading = analogRead(mPin);
  return (5.0 * reading * 100.0) / 1024;
}
