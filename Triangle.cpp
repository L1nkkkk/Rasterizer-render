#include "Triangle.h"

void Triangle::world2Screen(int width,int height)
{
    for(int i=0;i<3;++i)
    {
        this->screen_coords[i] = Vector2i((verts_[i].x+1.)*width/2., (verts_[i].y+1.)*height/2.);
    }
}

bool Triangle::isInside(const Vector2i& pos) const
{
    Vector3f t0(verts_[0].x,verts_[0].y,1);
    Vector3f t1(verts_[1].x,verts_[1].y,1);
    Vector3f t2(verts_[2].x,verts_[2].y,1);
    Vector3f f0,f1,f2;
    f0 = t1.cross(t0);
    f1 = t2.cross(t1);
    f2 = t0.cross(t2);
    Vector3f p(pos.x,pos.y,1.);
    if((p.dot(f0)*f0.dot(t2)>0) && (p.dot(f1)*f1.dot(t0)>0) && (p.dot(f2)*f2.dot(t1)>0))
        return true;
    return false;
}

std::tuple<float,float,float> Triangle::getBarycentricCoord(float x,float y)
{
    float alpha = (-(x-v_homogeneous[1].x)*(v_homogeneous[2].y-v_homogeneous[1].y)+(y-v_homogeneous[1].y)*(v_homogeneous[2].x-v_homogeneous[1].x))/
                  (-(v_homogeneous[0].x-v_homogeneous[1].x)*(v_homogeneous[2].y-v_homogeneous[1].y)+(v_homogeneous[0].y-v_homogeneous[1].y)*(v_homogeneous[2].x-v_homogeneous[1].x));
    float beta  = (-(x-v_homogeneous[2].x)*(v_homogeneous[0].y-v_homogeneous[2].y)+(y-v_homogeneous[2].y)*(v_homogeneous[0].x-v_homogeneous[2].x))/
                  (-(v_homogeneous[1].x-v_homogeneous[2].x)*(v_homogeneous[0].y-v_homogeneous[2].y)+(v_homogeneous[1].y-v_homogeneous[2].y)*(v_homogeneous[0].x-v_homogeneous[2].x));
    return {alpha,beta,1.-alpha-beta};
}