#pragma once
#ifndef __MODEL_H__
#define __MODEL_H__

#include "Vector.h"
#include <vector>
#include "Triangle.h"

class Model
{
private:
    
public:
    std::vector<Vector3f> verts_;
    std::vector<Triangle> faces_;
    std::vector<Vector3f> texcoords_;
    TGAImage normalMap;
    TGAImage diffuseMap;
    TGAImage specMap;
    Vector3f position;
    Vector3f rotation;
    Vector3f scale;
    Model(const char *filename);
    ~ Model();
    int num_verts();
    int num_faces();
    Vector3f vert(int i);
    Vector3f texcoord(int i);
	Triangle face(int idx);
};

#endif //__MODEL_H__