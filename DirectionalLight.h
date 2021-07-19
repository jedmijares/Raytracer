#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "Light.h"
#include "Vector3.h"

namespace Light
{

    class DirectionalLight : public Light
    {
    private:
        Vector3 direction_;

    public:
        DirectionalLight(float intensityIn, Vector3 direction);
        virtual float computeLighting(Vector3 point, Vector3 normal);
    };

    DirectionalLight::DirectionalLight(float intensityIn, Vector3 direction)
        : direction_{direction}
    {
        intensity = intensityIn;
    }

    float DirectionalLight::computeLighting(Vector3 point, Vector3 normal)
    {
        float nDotL = normal.dot(direction_);
        if (nDotL > 0)
        {
            return intensity * nDotL / (normal.length() * direction_.length());
        }
        return 0;
    }
} // namespace Light

#endif