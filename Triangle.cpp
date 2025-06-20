#include "Triangle.h"

bool Triangle::isInside(const Vector2i& pos) const
{
    Vector3f t0(v_homogeneous[0].x,v_homogeneous[0].y,1);
    Vector3f t1(v_homogeneous[1].x,v_homogeneous[1].y,1);
    Vector3f t2(v_homogeneous[2].x,v_homogeneous[2].y,1);
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