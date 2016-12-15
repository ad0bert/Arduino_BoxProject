#ifndef _LOOK_UP_H
#define _LOOK_UP_H

typedef struct minMaxVal {
  float min;
  float max;
} minMaxVal;

const int TABLE_SIZE = 2;

const minMaxVal PRODUCT_TABLE[TABLE_SIZE][3] = 
      { { {0, 25},{1, 2},{20, 25} },
      { {0, 90},{3, 4},{20, 22} }};


class LookUp{
  private:
    minMaxVal mLight;
    minMaxVal mWeight;
    minMaxVal mTemp;
  
  public:
    LookUp(float weight);
    short checkTemp (float temp);
    int  getCount(float weight);
    short checkLight(float light);
};
#endif // _LOOK_UP_H
