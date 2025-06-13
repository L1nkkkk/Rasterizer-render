#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include "Vector.h"
#include <vector>
#include "model.h"
#include "light.h"
#include "global.h"
#include "Matrix.h"

class Camera
{
private:
    /* data */
public:
    Vector3f look_at;
    Vector3f pos;
    float fov;
    float aspect_ratio;
    float z_near;
    float z_far;
    Vector3f up;
    Camera(){}
    Camera(Vector3f lookat,Vector3f pos_,float fov_,float aspect_ratio_,float z_near_,float z_far_):
        look_at(lookat.normalize()),
        pos(pos_),fov(fov_),aspect_ratio(aspect_ratio_),
        z_near(z_near_),z_far(z_far_)
    {
        Vector3f world_up(0,1,0);
        if(std::abs(look_at.dot(Vector3f(0,1,0))-1.)<EPSILON) world_up = Vector3f(1,0,0);
        up = (look_at.cross(world_up).normalize()).cross(look_at);
        up.normalized();
    }
    ~Camera(){};
};

class Scene
{
private:
    /* data */
public:
    std::vector<Model*> models;
    std::vector<Light> Lights;
    Camera& camera;
    Scene(Camera& camera_) : camera(camera_){}
    ~Scene() {}
    void addModel(Model*);
    void addLight(Light&);
    void addLight(Light);
};


#endif