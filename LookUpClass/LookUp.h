#ifndef _LOOK_UP_H
#define _LOOK_UP_H

typedef struct minMaxVal {
  float min;
  float max;
} minMaxVal;

const int TABLE_SIZE = 2;

const minMaxVal PRODUCT_TABLE[TABLE_SIZE][4] = {
      // LIGHT   WEIGHT    TEMP     Vibration
      { {0, 25}, {1.0, 2.0}, {25, 25.5}, { 1000, 1050 } },
      { {0, 90}, {3.0, 4.0}, {20, 25.0}, { 1000, 1030 } }};


class LookUp{
  private:
    minMaxVal mLight;
    minMaxVal mWeight;
    minMaxVal mTemp;
    minMaxVal mVib;
  
  public:
    LookUp(float weight);
    short checkTemp (float temp);
    int  getCount(float weight);
    short checkLight(float light);
    short checkVib(float vib);
};
#endif // _LOOK_UP_H
