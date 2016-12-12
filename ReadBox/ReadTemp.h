#ifndef _READ_TEMP_H
#define _READ_TEMP_H

#include <Arduino.h>

class ReadTemp{
  private:
    int mPin;
  
  public:
    ReadTemp(int pin) : mPin(pin){}
    double getTemp();
};
#endif // _READ_TEMP_H
