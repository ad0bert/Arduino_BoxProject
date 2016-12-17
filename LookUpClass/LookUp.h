#ifndef _LOOK_UP_H
#define _LOOK_UP_H

typedef struct minMaxVal {
  float min;
  float max;
} minMaxVal;

const int TABLE_SIZE = 2;

const minMaxVal PRODUCT_TABLE[TABLE_SIZE][4] = {
      // LIGHT   WEIGHT         TEMP        Vibration
      { {0, 50}, {10.0, 15.0}, {25, 25.5}, {1000, 1000} },
      { {0, 90}, {20.0, 25.0}, {20, 25.0}, {1000, 1000} }};


class LookUp{
  private:
    minMaxVal mLight;
    minMaxVal mWeight;
    minMaxVal mTemp;
    minMaxVal mVib;
    
    bool lightErr = false;
    short lightErrRet;
    
    bool tempErr = false;
    short tempErrRet;
    
    bool vibErr = false;
    bool vibErrRet;
  public:
    LookUp(float weight);
    short checkTemp (float &temp);
    int  getCount(float weight);
    short checkLight(float &light, bool isOut);
    short checkVib(float &vib);
};
#endif // _LOOK_UP_H
