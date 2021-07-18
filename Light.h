#ifndef LIGHT
#define LIGHT

#include "Vector3.h"

namespace Light
{
    class Light
    {
    public:
        float intensity;
        virtual float computeLighting(Vector3 point, Vector3 normal) = 0;
    };
} // namespace Light

#endif