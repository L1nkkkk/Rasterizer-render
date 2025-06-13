#pragma once
#ifndef __RENDER_H__
#define __RENDER_H__

#include "tgaimage.h"
#include "Vector.h"
#include "model.h"
#include "Triangle.h"
#include "scene.h"
#include "Matrix.h"
#include "Shader.h"

class Render
{
private:
    /* data */
    
public:
    TGAImage& image;
    int width,height;
    std::vector<float> zBuffer;
    Matrix4f viewport_mat;
    Shader* shader;
    Render(TGAImage& img,shader_type type_)
    : image(img)
    , width(img.get_width())
    , height(img.get_height())
    , zBuffer(width * height, std::numeric_limits<float>::lowest())
    {
        viewport_mat = Matrix4f({
            Vector4f(width/2.,0,0,width/2.),
            Vector4f(0,height/2.,0,height/2.),
            Vector4f(0,0,1,0),
            Vector4f(0,0,0,1)
        });

        switch (type_)
        {
        case shader_type::Phong_Shading:
            shader = new PhongShader();
            break;
        
        default:
            throw std::runtime_error("Unsupported shader type");
        }
    }
    ~Render() {}
    void drawLine(Vector2i& p0,Vector2i& p1,TGAImage& image,TGAColor color);
    void drawLine(Vector2f& p0,Vector2f& p1,TGAImage& image,TGAColor color);
    void drawLine(const Vector2i& p0,const Vector2i& p1,TGAImage& image,TGAColor color);
    void drawModel(Model* model);
    void drawTriangle(Triangle& triangle);
    void renderScene(Scene& scene);
    int getIndexBy2D(int x,int y) {return y*width+x;}

    Matrix4f getModelMatrix(Model*);
    Matrix4f getViewMatrix(Camera);
    Matrix4f getProjectionMatrix(Camera);
};



#endif //__RENDER_H_
