#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

#include "tgaimage.h"
#include "Triangle.h"
#include "Matrix.h"

enum class shader_type
{
   Phong_Shading
};

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
        for(int i=0;i<3;++i) tri.verts_[i]=Vector3f(tri.v_homogeneous[i].x,tri.v_homogeneous[i].y,tri.v_homogeneous[i].z);
    } 
    virtual bool vert_prosess(Matrix4f&,Triangle&) = 0;
    virtual bool fragment_prosess(Triangle& ,TGAColor&) = 0;
};

class PhongShader:public Shader
{
private:
    /* data */
public:
    PhongShader(Matrix4f viewprot_matrix_){ viewprot_matrix = viewprot_matrix_;};
    ~PhongShader(){};
    bool vert_prosess (Matrix4f&,Triangle&)override;
    bool fragment_prosess(Triangle&,TGAColor&) override;
};

#endif