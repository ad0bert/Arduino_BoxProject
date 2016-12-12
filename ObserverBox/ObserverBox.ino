#include "ReadTemp.h"

ReadTemp *rt;


void setup(){
  Serial.begin(9600);
  rt = new ReadTemp(A0);
}

void loop(){
  Serial.println(rt->getTemp());
  delay(1000); 
}
