#include "ReadTemp.h"
int segPins[8] = {5,6,7,8,9,10,11,12};
  
int numbers[10][8]  = {{1,1,1,1,1,0,1,0}, // zero
                       {0,0,1,0,0,0,1,0}, // one
                       {1,0,1,1,1,0,0,1}, // two
                       {1,0,1,0,1,0,1,1}, // three
                       {0,1,1,0,0,0,1,1}, // four
                       {1,1,0,0,1,0,1,1}, // five
                       {1,0,0,1,1,0,1,1}, // six
                       {1,0,1,0,0,0,1,0}, // seven
                       {1,1,1,1,1,0,1,1}, // eight
                       {1,1,1,0,1,0,1,1}};// nine
int latchPin = 3;
int clockPin = 4;
int dataPin = 2;

byte data;

ReadTemp *rt;
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
  rt = new ReadTemp(A0);
  
  for (int i = 0; i < 8; ++i){
    pinMode(segPins[i], OUTPUT);
    digitalWrite(segPins[i], LOW);
  }
}

void loop() {
  float temp = rt->getTemp();
  delay(5);
  if (temp > 24.0 && temp < 25.0) data = 0x0B;
  else if (temp > 25.0) data = 0x07;
  else if (temp < 24.0) data = 0x0D;
  showNumber(temp);
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
