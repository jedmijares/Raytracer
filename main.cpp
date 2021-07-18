#include "Vector3.h"
#include "Sphere.h"
#include "Light.h"
#include "PointLight.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include <SDL2/SDL.h>
#include <limits>
#include <cmath>
#include <utility>
#include <vector>
#include <memory>

const int CANVAS_WIDTH = 1280;
const int CANVAS_HEIGHT = 1280;

const int VIEWPORT_WIDTH = 10;
const int VIEWPORT_HEIGHT = 10;
const int VIEWPORT_DISTANCE = 10;

std::vector<Sphere> spheres;
std::vector<std::unique_ptr<Light::Light>> lights;

Vector3 canvasToViewport(int x, int y);
SDL_Color traceRay(Vector3 origin, Vector3 direction, float tMin, float tMax);
std::pair<float, float> intersectRaySphere(Vector3 origin, Vector3 direction, Sphere sphere);
float computeLighting(Vector3 point, Vector3 normal);
SDL_Color scaleColor(SDL_Color original, float intensity);

SDL_Color BACKGROUND_COLOR = SDL_Color{255, 255, 255, 255}; // white

int main()
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        SDL_CreateWindowAndRenderer(CANVAS_WIDTH, CANVAS_HEIGHT, 0, &window, &renderer);
    }

    spheres.emplace_back(
        Sphere(
            Vector3(0, -1, 3),
            1,
            SDL_Color{255, 0, 0, 255}));
    spheres.emplace_back(
        Sphere(
            Vector3(2, 0, 4),
            1,
            SDL_Color{0, 0, 255, 255}));
    spheres.emplace_back(
        Sphere(
            Vector3(-2, 0, 4),
            1,
            SDL_Color{0, 255, 0, 255}));

    // Light::DirectionalLight test(0.2, Vector3(1, 4, 4));
    // lights.emplace_back(test);
    lights.emplace_back(std::make_unique<Light::AmbientLight>(0.2));
    lights.emplace_back(std::make_unique<Light::PointLight>(0.6, Vector3(2, 1, 0)));
    lights.emplace_back(std::make_unique<Light::DirectionalLight>(0.2, Vector3(1, 4, 4)));

    Vector3 cameraPos{0, 0, 0};
    for (int x = -CANVAS_WIDTH / 2; x < CANVAS_WIDTH / 2; ++x)
    {
        for (int y = -CANVAS_HEIGHT / 2; y < CANVAS_HEIGHT / 2; ++y)
        {
            Vector3 direction = canvasToViewport(x, y);
            SDL_Color color = traceRay(cameraPos, direction, 0.2, std::numeric_limits<float>::infinity());
            SDL_SetRenderDrawColor(renderer, color.r, color.b, color.g, color.a);
            SDL_RenderDrawPoint(renderer, -x + CANVAS_WIDTH / 2, -y + CANVAS_HEIGHT / 2);
        }
    }

    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (1)
    {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

Vector3 canvasToViewport(int x, int y)
{
    return Vector3{(float)x * VIEWPORT_WIDTH / CANVAS_WIDTH, (float)y * VIEWPORT_HEIGHT / CANVAS_HEIGHT, VIEWPORT_DISTANCE};
}

SDL_Color traceRay(Vector3 origin, Vector3 direction, float tMin, float tMax)
{
    float closestT = std::numeric_limits<float>::infinity();
    Sphere *closestSphere = nullptr;
    for (auto &&sphere : spheres)
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
    if (closestSphere)
    {
        Vector3 point = origin + direction * closestT; // find intersection
        Vector3 normal = point - closestSphere->center;
        normal = normal * (1.0 / normal.length());
        float intensity = computeLighting(point, normal);
        return scaleColor(closestSphere->color, intensity);
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

float computeLighting(Vector3 point, Vector3 normal)
{
    float intensity = 0;
    for (auto &&light : lights)
    {
        intensity += light->computeLighting(point, normal);
    }
    return intensity;
}

SDL_Color scaleColor(SDL_Color original, float intensity)
{
    return SDL_Color{
        (uint8_t)(original.r * intensity),
        (uint8_t)(original.b * intensity),
        (uint8_t)(original.g * intensity),
        (uint8_t)(original.a * intensity)};
}