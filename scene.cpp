#include "scene.h"

void Scene::addModel(Model* model)
{
    this->models.push_back(model);
}
void Scene::addLight(Light& light)
{
    this->Lights.push_back(light);
}
void Scene::addLight(Light light)
{
    this->Lights.push_back(light);
}