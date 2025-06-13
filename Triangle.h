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
    std::vector<Vector2i> screen_coords;
    std::vector<Vector3f> uv_coords;
    std::vector<Vector4f> v_homogeneous;
    TGAImage* diffuse_map;
    TGAImage* normal_map;
    Vector3f normal;

    Triangle() : verts_(3,Vector3f(0)),screen_coords(3,Vector2i(0)),uv_coords(3,Vector3f(0)),v_homogeneous(3,Vector4f(0)){};
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
    void world2Screen(int width,int height);

    void setUVcoords(std::vector<Vector3f> uv_coords_){
        if(uv_coords_.size()!=3) return;
        uv_coords[0]=uv_coords_[0];
        uv_coords[1]=uv_coords_[1];
        uv_coords[2]=uv_coords_[2];
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
        int px = int(fx + 0.5f);
        int py = int(fy+ 0.5f);
        return diffuse_map->get(px,py);
    }
    
};


#endif