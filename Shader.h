#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

#include "tgaimage.h"
#include "Triangle.h"
#include "Matrix.h"
#include "Vector.h"
#include "light.h"

enum class shader_type
{
   Phong_Shading
};

typedef struct
{
    Vector3f& tex_coord;
    Vector3f& normal_coord;
    Vector3f& frag_pos;
    Vector3f& eye_pos;

    Triangle* obj;
    Light* lights;

} ShadingPixel;

class Shader
{
private:
    /* data */
protected:
    Matrix4f viewprot_matrix;
public:
    Shader(/* args */){};
    ~Shader(){};
    inline void transVerts(Matrix4f& mat,Triangle& tri)
    {
        for(auto& vert : tri.v_homogeneous){
            vert=mat*vert;
            vert.print();
            vert[0]=vert[0]/vert[3];
            vert[1]=vert[1]/vert[3];
            vert[2]=vert[2]/vert[3];
            //vert.print();
        }
    } 
    virtual bool vert_prosess(Matrix4f&,Triangle&) = 0;
    virtual bool fragment_prosess(ShadingPixel,TGAColor&) = 0;
};

class PhongShader:public Shader
{
private:
    /* data */
public:
    PhongShader(Matrix4f viewprot_matrix_){ viewprot_matrix = viewprot_matrix_;};
    ~PhongShader(){};
    bool vert_prosess (Matrix4f&,Triangle&)override;
    bool fragment_prosess(ShadingPixel,TGAColor&) override;
};

#endif