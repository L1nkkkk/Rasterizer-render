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
    float p = 150;
    Vector3f ka(0.05);
    Vector3f c(0);
    TGAColor pcolor = pix.obj->getColor(pix.tex_coord);
    TGAColor pnormal  = pix.obj->getNormal(pix.tex_coord);
    TGAColor scolor = pix.obj->getSpec(pix.tex_coord);
    Vector3f kd(pcolor.r,pcolor.g,pcolor.b);
    Vector3f ks(scolor.r,scolor.g,scolor.b);
    Vector3f n(pnormal.r,pnormal.g,pnormal.b);
    Vector3f amb_light_intensity(10, 10, 10);
    n.normalized();
    Vector3f v=(pix.eye_pos-pix.frag_pos).normalize();
    for(auto& light : pix.lights)
    {
        Vector3f l = light.pos-pix.frag_pos;
        float r2 = l.norm2();
        l.normalized();
        c = c + kd.cwise(light.intensity/r2)*(std::max(0.f,n.dot(l)));
        
        Vector3f h = (v+l).normalize();
        c = c + ks.cwise(light.intensity/r2)*pow(std::max(0.f,n.dot(h)),p);
        c = c + ka.cwise(amb_light_intensity);

    }
    color.r=c.x<255.?c.x:255;
    color.g=c.y<255.?c.y:255;
    color.b=c.z<255.?c.z:255;
    return true;
}

