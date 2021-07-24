
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
    Sphere(Vector3 centerIn, float radiusIn, SDL_Color colorIn, float specularIn);
    ~Sphere();
};

Sphere::Sphere(Vector3 centerIn, float radiusIn, SDL_Color colorIn, float specularIn)
{
    center = centerIn;
    radius = radiusIn;
    color = colorIn;
    specular = specularIn;
}

Sphere::~Sphere()
{
}
