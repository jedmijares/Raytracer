#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "Light.h"
#include "PointLight.h"
#include "Scene.h"
#include "Sphere.h"
#include "Utility.h"
#include "Vector3.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include <memory>
#include <utility>
#include <vector>

Scene scene;

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

    scene.spheres.emplace_back(
        Sphere(
            Vector3(0, -1, 3),
            1,
            SDL_Color{255, 0, 0, 255},
            500));
    scene.spheres.emplace_back(
        Sphere(
            Vector3(2, 0, 4),
            1,
            SDL_Color{0, 0, 255, 255},
            500));
    scene.spheres.emplace_back(
        Sphere(
            Vector3(-2, 0, 4),
            1,
            SDL_Color{0, 255, 0, 255},
            10));
    scene.spheres.emplace_back(
        Sphere(
            Vector3(0, -5001, 0),
            5000,
            SDL_Color{255, 255, 0, 255},
            1000));

    scene.lights.emplace_back(std::make_shared<Light::AmbientLight>(0.2));
    scene.lights.emplace_back(std::make_shared<Light::PointLight>(0.6, Vector3(2, 1, 0)));
    scene.lights.emplace_back(std::make_shared<Light::DirectionalLight>(0.2, Vector3(1, 4, 4)));

    Vector3 cameraPos{0, 0, 0};
    for (int x = -CANVAS_WIDTH / 2; x < CANVAS_WIDTH / 2; ++x)
    {
        for (int y = -CANVAS_HEIGHT / 2; y < CANVAS_HEIGHT / 2; ++y)
        {
            Vector3 direction = canvasToViewport(x, y);
            SDL_Color color = traceRay(cameraPos, direction, 0.2, std::numeric_limits<float>::infinity());
            SDL_SetRenderDrawColor(renderer, color.r, color.b, color.g, color.a);
            SDL_RenderDrawPoint(renderer, x + CANVAS_WIDTH / 2, -y + CANVAS_HEIGHT / 2);
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