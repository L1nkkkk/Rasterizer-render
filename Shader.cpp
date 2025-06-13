#include "Shader.h"
//Phong Shading
bool PhongShader::vert_prosess(Matrix4f& mvp,Triangle& tri)
{
    transVerts(mvp,tri);
    transVerts(viewprot_matrix,tri);
    return true;
}

bool PhongShader::fragment_prosess(ShadingPixel pix,TGAColor& color)
{
    return true;
}

