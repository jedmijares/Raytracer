#ifndef AMBIENT_LIGHT
#define AMBIENT_LIGHT

#include "Light.h"

namespace Light
{
    class AmbientLight : public Light
    {
    public:
        AmbientLight(float intensityIn);
        float computeLighting(Vector3 point, Vector3 normal, Vector3 viewDir, float specular);
    };

    AmbientLight::AmbientLight(float intensityIn)
    {
        intensity = intensityIn;
    }

    float AmbientLight::computeLighting(Vector3 point, Vector3 normal, Vector3 viewDir, float specular)
    {
        return intensity;
    }
} // namespace Light

#endif