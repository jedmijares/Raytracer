#ifndef AMBIENT_LIGHT
#define AMBIENT_LIGHT

#include "Light.h"

namespace Light
{

    class AmbientLight : virtual public Light
    {
    public:
        AmbientLight(float intensityIn);
        float computeLighting(Vector3 point, Vector3 normal);
    };

    AmbientLight::AmbientLight(float intensityIn)
    {
        intensity = intensityIn;
    }

    float AmbientLight::computeLighting(Vector3 point, Vector3 normal)
    {
        return intensity;
    }

} // namespace Light

#endif