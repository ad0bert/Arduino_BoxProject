#include "Wire.h"
#include "LookUp.h"

const int outerPressurePin = A3;
const int innerPressurePin = A0;

const int innerLightG = 10;
const int innerLightR = 11;

const int outerLightR = 12;
const int outerLightG = 13;

const int innerLightPin = A1;
const int outerLightPin = A2;

int innerPressureValue = 0;
float innerLightValue = 0;
float outerLightValue = 0;

int pins[8] =          {2,3,4,5,6,7,8,9};
//                      d,d,-,-,
int sevenSeg[11][8]= { {1,1,0,0,0,0,0,0}, // 0
                       {1,1,1,1,1,0,0,1}, // 1
                       {1,0,1,0,0,1,0,0}, // 2
                       {1,0,1,1,0,0,0,0}, // 3
                       {1,0,0,1,1,0,0,1}, // 4
                       {1,0,0,1,0,0,1,0}, // 5
                       {1,0,0,0,0,0,1,0}, // 6
                       {1,1,1,1,1,0,0,0}, // 7
                       {1,0,0,0,0,0,0,0}, // 8
                       {1,0,0,1,0,0,0,0}, // 9
                       {1,1,1,1,1,1,1,1}};


void updateSegments(int val){
  int *number = sevenSeg[val];
  for(int i=0;i < 8 ;i++){
    if(number[i] == 1){
      digitalWrite(pins[i],LOW);
    }
    else{
      digitalWrite(pins[i],HIGH);
    }
  }
}

LookUp *lu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lu = NULL;
  pinMode(innerPressurePin, INPUT);
  pinMode(outerPressurePin, INPUT);
  
  pinMode(innerLightPin, INPUT);
  pinMode(outerLightPin, INPUT);
  
  pinMode(innerLightR, OUTPUT);
  pinMode(innerLightG, OUTPUT);
  
  pinMode(outerLightR, OUTPUT);
  pinMode(outerLightG, OUTPUT);
  
  for (int i = 0; i < 8; ++i){
    pinMode(pins[i], OUTPUT);
  }
  
  digitalWrite(outerLightR, HIGH);
  digitalWrite(outerLightG, HIGH);
  digitalWrite(innerLightR, HIGH);
  digitalWrite(innerLightG, HIGH);
  
  updateSegments(10);
}

bool isClosed(){
  Serial.println(analogRead(outerPressurePin));
  return analogRead(outerPressurePin) > 0;
}

void sendBroadCast(int stat, int weight){
  Wire.beginTransmission(8);
  Wire.write(stat);
  Wire.endTransmission();
  if (stat == 0) {
    Wire.beginTransmission(8);
    Wire.write(weight);
    Wire.endTransmission();
  }
}

void loop() {
  innerPressureValue = analogRead(innerPressurePin)-550;
  innerLightValue = analogRead(innerLightPin);
  outerLightValue = analogRead(outerLightPin);
  Serial.println(innerPressureValue);
  //Serial.print("InnerLight: ");Serial.println(innerLightValue);
  //Serial.print("OuterLight: ");Serial.println(outerLightValue);
  if (isClosed()){
    if (lu == NULL) lu = new LookUp(innerPressureValue);
    if (lu->getCount(innerPressureValue) == 0) {delete lu; lu = NULL; updateSegments(10);}
    else updateSegments(lu->getCount(innerPressureValue));
    sendBroadCast(0, innerPressureValue); 
  }
    if (lu != NULL){
      if(lu->checkLight(innerLightValue, false) == 0){
        digitalWrite(innerLightG, LOW);
        digitalWrite(innerLightR, HIGH);
      } else {
        digitalWrite(innerLightG, HIGH);
        digitalWrite(innerLightR, LOW);
      }
      if(lu->checkLight(outerLightValue, true) == 0){
        digitalWrite(outerLightG, LOW);
        digitalWrite(outerLightR, HIGH);
      } else {
        digitalWrite(outerLightG, HIGH);
        digitalWrite(outerLightR, LOW);
      }
    } else {
        digitalWrite(outerLightR, HIGH);
        digitalWrite(outerLightG, HIGH);
        digitalWrite(innerLightR, HIGH);
        digitalWrite(innerLightG, HIGH);      
    }
  
  
  
  delay(100);
}
