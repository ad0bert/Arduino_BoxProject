#ifndef _READ_ANALOG_H
#define _READ_ANALOG_H

#include <Arduino.h>

class ReadAnalog{
  private:
    int mPin;
  
  public:
    ReadAnalog(int pin) : mPin(pin){}
    double getTemp();
    double readShake();
};
#endif // _READ_ANALOG_H
