#ifndef UTILITY
#define UTILITY

#include "Light.h"
#include "Scene.h"
#include "Sphere.h"
#include "Vector3.h"
#include <SDL2/SDL.h>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

extern Scene scene;

const int CANVAS_WIDTH = 1280;
const int CANVAS_HEIGHT = 1280;

const int VIEWPORT_WIDTH = 10;
const int VIEWPORT_HEIGHT = 10;
const int VIEWPORT_DISTANCE = 10;
SDL_Color BACKGROUND_COLOR = SDL_Color{0, 0, 0, 255}; // white

// translate canvas coordinate to position on viewport
Vector3 canvasToViewport(int x, int y);

// find closest sphere in given direction from given position
std::pair<Sphere *, float> closestIntersection(Vector3 origin, Vector3 direction, float tMin, float tMax);

// trace a ray from origin to find what color to display
SDL_Color traceRay(Vector3 origin, Vector3 direction, float tMin, float tMax, uint8_t reflectionRecursionDepth);

// find where a ray intersects with a sphere
std::pair<float, float> intersectRaySphere(Vector3 origin, Vector3 direction, Sphere sphere);

// return intensity of lighting at a point on an object
float computeLighting(Vector3 point, Vector3 normal, Vector3 viewDir, float specular);

// scale color by given intensity
SDL_Color scaleColor(SDL_Color original, float intensity);

// return a value within provided range
float clamp(float orig, float min, float max);

// reflects a ray across a surface's normal
Vector3 reflectRay(Vector3 ray, Vector3 normal);

Vector3 canvasToViewport(int x, int y)
{
    return Vector3{(float)x * VIEWPORT_WIDTH / CANVAS_WIDTH, (float)y * VIEWPORT_HEIGHT / CANVAS_HEIGHT, VIEWPORT_DISTANCE};
}

std::pair<Sphere *, float> closestIntersection(Vector3 origin, Vector3 direction, float tMin, float tMax)
{
    float closestT = std::numeric_limits<float>::infinity();
    Sphere *closestSphere = nullptr;
    for (auto &&sphere : scene.spheres)
    {
        auto ts = intersectRaySphere(origin, direction, sphere);
        if (ts.first >= tMin && ts.first <= tMax && ts.first < closestT)
        {
            closestT = ts.first;
            closestSphere = &sphere;
        }
        if (ts.second >= tMin && ts.second <= tMax && ts.second < closestT)
        {
            closestT = ts.second;
            closestSphere = &sphere;
        }
    }
    return std::make_pair(closestSphere, closestT);
}

SDL_Color traceRay(Vector3 origin, Vector3 direction, float tMin, float tMax, uint8_t reflectionRecursionDepth)
{
    auto intersection = closestIntersection(origin, direction, tMin, tMax);
    Sphere *closestSphere = intersection.first;
    float closestT = intersection.second;
    if (closestSphere)
    {
        Vector3 point = origin + direction * closestT; // find intersection point
        Vector3 normal = point - closestSphere->center;
        normal = normal * (1.0 / normal.length());
        float intensity = computeLighting(point, normal, -direction, closestSphere->specular);
        SDL_Color localColor = scaleColor(closestSphere->color, intensity);

        float reflective = closestSphere->reflective;
        if (reflective <= 0 || reflectionRecursionDepth <= 0)
        {
            return localColor;
        }
        SDL_Color reflectedColor = traceRay(point, reflectRay(-direction, normal), tMin, std::numeric_limits<float>::infinity(), reflectionRecursionDepth - 1);

        localColor = scaleColor(localColor, (1.0 - reflective));
        reflectedColor = scaleColor(reflectedColor, (reflective));
        return SDL_Color{
            (uint8_t)(clamp((float)localColor.r + (float)reflectedColor.r, 0.0, 255.0)),
            (uint8_t)(clamp((float)localColor.g + (float)reflectedColor.g, 0.0, 255.0)),
            (uint8_t)(clamp((float)localColor.b + (float)reflectedColor.b, 0.0, 255.0)),
            (uint8_t)(clamp((float)localColor.a + (float)reflectedColor.a, 0.0, 255.0))};
    }
    return BACKGROUND_COLOR;
}

std::pair<float, float> intersectRaySphere(Vector3 origin, Vector3 direction, Sphere sphere)
{
    float r = sphere.radius;
    Vector3 CO = origin - sphere.center;

    float a = direction.dot(direction);
    float b = 2 * CO.dot(direction);
    float c = CO.dot(CO) - r * r;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return std::pair<float, float>{std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};
    }

    float t1 = (-b + sqrt(discriminant)) / (2 * a);
    float t2 = (-b - sqrt(discriminant)) / (2 * a);

    return std::pair<float, float>{t1, t2};
}

float computeLighting(Vector3 point, Vector3 normal, Vector3 viewDir, float specular)
{
    float intensity = 0;
    for (auto &&light : scene.lights)
    {
        intensity += light->computeLighting(point, normal, viewDir, specular);
    }
    return intensity;
}

SDL_Color scaleColor(SDL_Color original, float intensity)
{
    return SDL_Color{
        (uint8_t)(clamp(original.r * intensity, 0, 255)),
        (uint8_t)(clamp(original.g * intensity, 0, 255)),
        (uint8_t)(clamp(original.b * intensity, 0, 255)),
        (uint8_t)(clamp(original.a * intensity, 0, 255))};
}

float clamp(float orig, float min, float max)
{
    if (orig > max)
    {
        return max;
    }
    if (orig < min)
    {
        return min;
    }
    return orig;
}

Vector3 reflectRay(Vector3 ray, Vector3 normal)
{
    return normal * 2 * normal.dot(ray) - ray;
}

#endif