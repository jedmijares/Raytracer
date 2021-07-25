#ifndef SPHERE
#define SPHERE

#include "Vector3.h"
#include <SDL2/SDL.h>

class Sphere
{
private:
public:
    Vector3 center;
    float radius;
    SDL_Color color;
    float specular;
    float reflective;
    Sphere(Vector3 centerIn, float radiusIn, SDL_Color colorIn, float specularIn, float reflectiveIn);
    ~Sphere();
};

Sphere::Sphere(Vector3 centerIn, float radiusIn, SDL_Color colorIn, float specularIn, float reflectiveIn)
{
    center = centerIn;
    radius = radiusIn;
    color = colorIn;
    specular = specularIn;
    reflective = reflectiveIn;
}

Sphere::~Sphere()
{
}

#endif