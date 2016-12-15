#include "LookUp.h"

LookUp::LookUp(float weight){
  int pos = -1;
  for (int i = 0; i < TABLE_SIZE; ++i){
    if (PRODUCT_TABLE[i][1].min > weight && PRODUCT_TABLE[i][1].max < weight)
      pos = i;
  }
  
  if (pos != -1){
    mLight.min = PRODUCT_TABLE[pos][0].min;
    mLight.max = PRODUCT_TABLE[pos][0].max;
    
    mWeight.min = PRODUCT_TABLE[pos][1].min;
    mWeight.max = PRODUCT_TABLE[pos][1].max;
    
    mTemp.min = PRODUCT_TABLE[pos][2].min;
    mTemp.max = PRODUCT_TABLE[pos][2].max;
  } else {
    mLight.min = -1;
    mLight.max = -1;
    
    mWeight.min = -1;
    mWeight.max = -1;
    
    mTemp.min = -1;
    mTemp.max = -1;
  }
}

short LookUp::checkTemp (float temp){
  if (temp < mTemp.min) return -1;
  if (temp > mTemp.max) return  1;
  return 0;  
}

int  LookUp::getCount(float weight){
  int count = weight / mWeight.min;
  return count;
}

short LookUp::checkLight(float light){
  if (light < mLight.min) return -1;
  if (light > mLight.max) return  1;
  return 0;
}

