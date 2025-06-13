#pragma once
#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "Vector.h"

class Light
{
public:
    Vector3f pos;
    Vector3f intensity;
public:
    Light():pos(Vector3f()),intensity(0){}
    Light(Vector3f d,Vector3f i):pos(d),intensity(i){}
    ~Light(){};
};


#endif