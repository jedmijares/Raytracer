#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "Light.h"
#include "Utility.h"
#include "Vector3.h"

namespace Light
{
    class DirectionalLight : public Light
    {
    private:
        Vector3 lightDir_;

    public:
        DirectionalLight(float intensityIn, Vector3 direction);
        virtual float computeLighting(Vector3 point, Vector3 normal, Vector3 viewDir, float specular);
    };

    DirectionalLight::DirectionalLight(float intensityIn, Vector3 direction)
        : lightDir_{direction}
    {
        intensity = intensityIn;
    }

    float DirectionalLight::computeLighting(Vector3 point, Vector3 normal, Vector3 viewDir, float specular)
    {
        auto shadower = closestIntersection(point, lightDir_, 0.001, std::numeric_limits<float>::infinity());
        if (shadower.first != nullptr)
        {
            return 0.0;
        }

        float returnIntensity = 0;

        float nDotL = normal.dot(lightDir_);
        if (nDotL > 0)
        {
            returnIntensity += intensity * nDotL / (normal.length() * lightDir_.length());
        }

        if (specular >= 0)
        {
            Vector3 reflectDir = normal * 2 * normal.dot(lightDir_) - lightDir_;
            float rDotV = reflectDir.dot(viewDir);
            if (rDotV > 0)
            {
                returnIntensity += intensity * pow(rDotV / (reflectDir.length() * viewDir.length()), specular);
            }
        }

        return returnIntensity;
    }
} // namespace Light

#endif