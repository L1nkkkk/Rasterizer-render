#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

enum class shader_type
{
   Phong_Shading
};

class Shader
{
private:
    /* data */
public:
    Shader(/* args */){};
    ~Shader(){};
    virtual bool vert_prosess() = 0;
};

class PhongShader:public Shader
{
private:
    /* data */
public:
    PhongShader(){};
    ~PhongShader(){};
    bool vert_prosess ()override;
};

#endif