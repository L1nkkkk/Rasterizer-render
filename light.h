#pragma once
#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "Vector.h"

class Light
{
public:
    Vector3f dir;
    float intensity;
public:
    Light():dir(Vector3f()),intensity(0){}
    Light(Vector3f d,float i):dir(d),intensity(i){}
    ~Light(){};
};


#endif