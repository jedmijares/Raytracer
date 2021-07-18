#ifndef POINT_LIGHT
#define POINT_LIGHT

#include "Light.h"
#include "Vector3.h"

namespace Light
{

    class PointLight : public Light
    {
    private:
        Vector3 position_;

    public:
        PointLight(float intensityIn, Vector3 position);
        Vector3 getPosition();
        virtual float computeLighting(Vector3 point, Vector3 normal);
    };

    PointLight::PointLight(float intensityIn, Vector3 position)
        : position_{position}
    {
        intensity = intensityIn;
    }

    float PointLight::computeLighting(Vector3 point, Vector3 normal)
    {
        Vector3 direction = position_ - point;
        float nDotL = normal.dot(direction);
        if (nDotL > 0)
        {
            return intensity * nDotL / (normal.length() * direction.length());
        }
        return 0;
    }

    Vector3 PointLight::getPosition()
    {
        return position_;
    }

} // namespace Light

#endif