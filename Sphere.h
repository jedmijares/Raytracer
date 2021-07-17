
#include "Vector3.h"
#include <SDL2/SDL.h>

class Sphere
{
private:
public:
    Vector3 center;
    float radius;
    uint32_t color;
    Sphere(Vector3 centerIn, float radiusIn, uint32_t colorIn);
    ~Sphere();
};

Sphere::Sphere(Vector3 centerIn, float radiusIn, uint32_t colorIn)
{
    center = centerIn;
    radius = radiusIn;
    color = colorIn;
}

Sphere::~Sphere()
{
}
