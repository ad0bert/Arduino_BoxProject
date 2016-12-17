#include "Wire.h"
#include "ReadAnalog.h"
#include "LookUp.h"

#define SHAKE 0

int segPins[8] = {5,6,7,8,9,10,11,12};
  
int numbers[10][8]  = {{1,1,1,1,1,0,1,0}, // zero
                       {0,0,1,0,0,0,1,0}, // one
                       {1,0,1,1,1,0,0,1}, // two
                       {1,0,1,0,1,0,1,1}, // three
                       {0,1,1,0,0,0,1,1}, // four
                       {1,1,0,0,1,0,1,1}, // five
                       {1,1,0,1,1,0,1,1}, // six
                       {1,0,1,0,0,0,1,0}, // seven
                       {1,1,1,1,1,0,1,1}, // eight
                       {1,1,1,0,1,0,1,1}};// nine
int latchPin = 3;
int clockPin = 4;
int dataPin = 2;

byte data;

float val = 0;

ReadAnalog *ra;
LookUp *lu;

const int nbrDigits= 4;

void showNumber( int number){
   if(number == 0) {
      showDigit( 0, nbrDigits-1) ;
   } else {
      for( int digit = nbrDigits-1; digit >= 0; digit--)  {
         if(number > 0)  {
            showDigit( number % 10, digit) ;
            number = number / 10;
         }
      }
   }
} 
 
void showDigit( int number, int digit)
{
  byte before = data;
  if      (digit == 0) data |= 0xB0;
  else if (digit == 1) data |= 0xD0;
  else if (digit == 2) data |= 0xE0;
  else if (digit == 3) data |= 0x70;
  
   digitalWrite(latchPin, 0);
   shiftOut(dataPin, clockPin, data);
   digitalWrite(latchPin, 1);
   
   for(int i = 0; i < 8; i++)  {
      digitalWrite( segPins[i], numbers[number][i]);
   }
   data = before;
   delay(5);
}

void setup() {
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);
  Wire.begin(8); // listen on A5
  Wire.onReceive(recive);
  ra = new ReadAnalog(A0);
  for (int i = 0; i < 8; ++i){
    pinMode(segPins[i], OUTPUT);
    digitalWrite(segPins[i], LOW);
  }
}

void loop() {
  #if SHAKE == 1
  val = ra->readShake();
  #else
  val = ra->getTemp();
  #endif
  
  delay(5);
  int ret = -1;
  #if SHAKE == 1
  if (lu != NULL) ret = lu->checkVib(val);
  #else
  if (lu != NULL) ret = lu->checkTemp(val);
  #endif
  
  if      (ret ==  0) data = 0x0B;
  else if (ret ==  1) data = 0x07;
  else if (ret == -1) data = 0x0D;
  
  showNumber(val);
}

void recive(int number){
  static float lastInput = -1;
  String i2cRec = "";
  while (Wire.available()){
    i2cRec += Wire.read();
  }
  char buffer[10];
  i2cRec.toCharArray(buffer, 10); 
  float res = atof(buffer);
  
  if (lastInput == 0){
     if (lu == NULL)
       lu = new LookUp(res);
     if (lu->getCount(res) == 0){
       delete lu;
       lu = NULL;
     }
  }
  lastInput = res;
  
}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }
    digitalWrite(myDataPin, pinState);
    digitalWrite(myClockPin, 1);
    digitalWrite(myDataPin, 0);
  }
  digitalWrite(myClockPin, 0);
}
