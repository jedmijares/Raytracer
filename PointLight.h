#ifndef POINT_LIGHT
#define POINT_LIGHT

#include "Light.h"
#include "Scene.h"
#include "Utility.h"
#include "Vector3.h"

// extern Scene scene;

namespace Light
{
    class PointLight : public Light
    {
    private:
        Vector3 position_;

    public:
        PointLight(float intensityIn, Vector3 position);
        virtual float computeLighting(Vector3 point, Vector3 normal, Vector3 viewDir, float specular);
    };

    PointLight::PointLight(float intensityIn, Vector3 position)
        : position_{position}
    {
        intensity = intensityIn;
    }

    float PointLight::computeLighting(Vector3 point, Vector3 normal, Vector3 viewDir, float specular)
    {
        Vector3 lightDir = position_ - point;
        auto shadower = closestIntersection(point, lightDir, 0.001, 1.0);
        if (shadower.first != nullptr)
        {
            return 0.0;
        }

        float returnIntensity = 0;
        float nDotL = normal.dot(lightDir);
        if (nDotL > 0)
        {
            returnIntensity += intensity * nDotL / (normal.length() * lightDir.length());
        }

        if (specular >= 0)
        {
            Vector3 reflectDir = normal * 2 * normal.dot(lightDir) - lightDir;
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