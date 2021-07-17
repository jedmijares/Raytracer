
#include "Vector3.h"
#include <SDL2/SDL.h>

class Sphere
{
private:
public:
    Vector3 center;
    float radius;
    SDL_Color color;
    Sphere(Vector3 centerIn, float radiusIn, SDL_Color colorIn);
    ~Sphere();
};

Sphere::Sphere(Vector3 centerIn, float radiusIn, SDL_Color colorIn)
{
    center = centerIn;
    radius = radiusIn;
    color = colorIn;
}

Sphere::~Sphere()
{
}
