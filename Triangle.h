#pragma once
#ifndef __TRIANGLE_H_
#define __TRIANGLE_H_

#include "Vector.h"
#include "tgaimage.h"
#include <vector>
#include <tuple>

class Triangle
{
private:
    
    
public:
    std::vector<Vector3f> verts_;
    std::vector<Vector3f> screen_coords;
    std::vector<Vector3f> uv_coords;
    std::vector<Vector3f> n_coords;
    std::vector<Vector4f> v_homogeneous;
    TGAImage* diffuse_map;
    TGAImage* normal_map;
    TGAImage* spec_map;
    Vector3f normal;

    Triangle() : verts_(3,Vector3f(0)),screen_coords(3,Vector3f(0)),uv_coords(3,Vector3f(0)),v_homogeneous(3,Vector4f(0)){};
    Triangle(std::vector<Vector3f> verts) : verts_(3),screen_coords(3),uv_coords(3),v_homogeneous(3){
        if(verts.size()!=3) return;
        v_homogeneous[0]=Vector4f(verts_[0] = verts[0]);
        v_homogeneous[1]=Vector4f(verts_[1] = verts[1]);
        v_homogeneous[2]=Vector4f(verts_[2] = verts[2]);
        normal = ((verts_[2]-verts_[0]).cross(verts_[1]-verts_[0])).normalize();
    }
    Triangle(std::vector<Vector3f> verts,const TGAColor c) : verts_(3),screen_coords(3),uv_coords(3),v_homogeneous(3){
        if(verts.size()!=3) return;
        verts_[0] = verts[0];
        verts_[1] = verts[1];
        verts_[2] = verts[2];
        color = c;
        normal = ((verts_[2]-verts_[0]).cross(verts_[1]-verts_[0])).normalize();
    }
    ~Triangle() {}
    bool isInside(const Vector2i& pos) const;
    void setColor(TGAColor c) {color=c;}
    inline Vector3f& operator[] (int idx) { return verts_[idx];}

    void setUVcoords(std::vector<Vector3f> uv_coords_){
        if(uv_coords_.size()!=3) return;
        uv_coords=uv_coords_;
    }

    void setNcoords(std::vector<Vector3f> n_coords_){
        if(n_coords_.size()!=3) return;
        n_coords = n_coords_;
    }
    std::tuple<float,float,float> getBarycentricCoord(float x,float y);

    TGAColor color;

    TGAColor getColor(Vector3f texcoords)
    {
        int width = diffuse_map->get_width();
        int height = diffuse_map->get_height();
        // 1. 先缩放到 [0, tex_width-1]×[0, tex_height-1]
        float fx = texcoords[0] * (width  - 1);
        float fy = texcoords[1] * (height - 1);

        // 2. 根据你的 UV 原点约定做翻转（这里假设 v=0 在底部）：
        return bilinearInterplate(*diffuse_map,fx,fy);
    }

    TGAColor getNormal(Vector3f texcoords)
    {
        int width = normal_map->get_width();
        int height = normal_map->get_height();
        // 1. 先缩放到 [0, tex_width-1]×[0, tex_height-1]
        float fx = texcoords[0] * (width  - 1);
        float fy = texcoords[1] * (height - 1);

        // 2. 根据你的 UV 原点约定做翻转（这里假设 v=0 在底部）：
        return bilinearInterplate(*normal_map,fx,fy);
    }

    TGAColor getSpec(Vector3f texcoords)
    {
        int width = normal_map->get_width();
        int height = normal_map->get_height();
        // 1. 先缩放到 [0, tex_width-1]×[0, tex_height-1]
        float fx = texcoords[0] * (width  - 1);
        float fy = texcoords[1] * (height - 1);
        // 2. 根据你的 UV 原点约定做翻转（这里假设 v=0 在底部）：
        return bilinearInterplate(*spec_map,fx,fy);
    }
    
    inline TGAColor Interplate(TGAColor p0,TGAColor p1,float t)
    {
        return TGAColor(
            ((float)p0.r*(1.-t)+(float)p1.r*t),
            ((float)p0.g*(1.-t)+(float)p1.g*t),
            ((float)p0.b*(1.-t)+(float)p1.b*t),
            ((float)p0.a*(1.-t)+(float)p1.a*t)
        );
    }

    inline TGAColor bilinearInterplate(TGAImage& img,float u,float v)
    {
        int u0=(int)u<img.get_width()?(int)u:img.get_width()-1;
        int u1=u0+1<img.get_width()?u0+1:u0;
        int v0=(int)v<img.get_height()?(int)v:img.get_height()-1;
        int v1=v0+1<img.get_height()?v0+1:v0;
        TGAColor p0 = img.get(u0,v0);
        TGAColor p1 = img.get(u0,v1);
        TGAColor p2 = img.get(u1,v0);
        TGAColor p3 = img.get(u1,v1);
        float s = ((int)v)+1-v;
        float t = ((int)u)+1-u;
        return Interplate(Interplate(p0,p1,s),Interplate(p2,p3,s),t);
    } 
};


#endif