#ifndef SCENE
#define SCENE

#include "Light.h"
#include "Sphere.h"
#include <memory>
#include <vector>

struct Scene
{
    std::vector<Sphere> spheres;
    std::vector<std::shared_ptr<Light::Light>> lights;
};

#endif