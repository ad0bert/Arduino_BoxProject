#include "LookUp.h"

LookUp::LookUp(float weight){
  int pos = -1;
  for (int i = 0; i < TABLE_SIZE; ++i){
    if (PRODUCT_TABLE[i][1].min < weight && PRODUCT_TABLE[i][1].max > weight){
      pos = i;
      break;
    }
  }
  
  if (pos != -1){
    mLight.min = PRODUCT_TABLE[pos][0].min;
    mLight.max = PRODUCT_TABLE[pos][0].max;
    
    mWeight.min = PRODUCT_TABLE[pos][1].min;
    mWeight.max = PRODUCT_TABLE[pos][1].max;
    
    mTemp.min = PRODUCT_TABLE[pos][2].min;
    mTemp.max = PRODUCT_TABLE[pos][2].max;
    
    mVib.min = PRODUCT_TABLE[pos][3].min;
    mVib.max = PRODUCT_TABLE[pos][3].max;
  } else {
    mLight.min = -1;
    mLight.max = -1;
    
    mWeight.min = -1;
    mWeight.max = -1;
    
    mTemp.min = -1;
    mTemp.max = -1;
    
    mVib.min = -1;
    mVib.max = -1;
  }
}

short LookUp::checkTemp (float &temp){
  if (tempErr){
     temp = mTemp.min;
     return tempErrRet;
  }
  if (temp < mTemp.min){
    tempErr = true;
    tempErrRet = -1;
    mTemp.min = mTemp.max = temp;
    return -1;
  }
  if (temp > mTemp.max){
    tempErr = true;
    tempErrRet = 1;
    mTemp.min = mTemp.max = temp;
    return 1;
  }
  return 0;  
}

int  LookUp::getCount(float weight){
  if (mWeight.min == -1) return 0;
  int count = weight / mWeight.min;
  return count;
}

short LookUp::checkLight(float &light, bool isOut){
  if (isOut) {
    if (light < mLight.min) return -1;
    if (light > mLight.max) return 1;
    return 0;
  }
  if (lightErr){
     light = mLight.min;
     return lightErrRet;
  }
  if (light < mLight.min){
    lightErr = true;
    lightErrRet = -1;
    mLight.min = mLight.max = light;
    return -1;
  }
  if (light > mLight.max){
    lightErr = true;
    lightErrRet = 1;
    mLight.min = mLight.max = light;
    return 1;
  }
  return 0; 
}

short LookUp::checkVib(float &vib){
  if (vibErr){
     vib = mVib.min;
     return vibErrRet;
  }
  if (vib < mVib.min){
    vibErr = true;
    vibErrRet = -1;
    mVib.min = mVib.max = vib;
    return -1;
  }
  return 0; 
}

