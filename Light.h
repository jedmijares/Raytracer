#ifndef LIGHT
#define LIGHT

#include "Vector3.h"

namespace Light
{
    class Light
    {
    public:
        float intensity;
        virtual float computeLighting(Vector3 point, Vector3 normal, Vector3 viewDir, float specular) = 0;
    };
} // namespace Light

#endif