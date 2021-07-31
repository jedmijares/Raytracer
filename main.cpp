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
#include <map>
#include <memory>
#include <thread>
#include <utility>
#include <vector>

Scene scene;

void findColors(const int minX, const int maxX, const int minY, const int maxY, const Vector3 cameraPos, std::map<std::pair<int, int>, SDL_Color> &pixelToColor);

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
            500,
            0.2));
    scene.spheres.emplace_back(
        Sphere(
            Vector3(2, 0, 4),
            1,
            SDL_Color{0, 0, 255, 255},
            500,
            0.3));
    scene.spheres.emplace_back(
        Sphere(
            Vector3(-2, 0, 4),
            1,
            SDL_Color{0, 255, 0, 255},
            10,
            0.4));
    scene.spheres.emplace_back(
        Sphere(
            Vector3(0, -5001, 0),
            5000,
            SDL_Color{255, 255, 0, 255},
            1000,
            0.5));

    scene.lights.emplace_back(std::make_shared<Light::AmbientLight>(0.2));
    scene.lights.emplace_back(std::make_shared<Light::PointLight>(0.6, Vector3(2, 1, 0)));
    scene.lights.emplace_back(std::make_shared<Light::DirectionalLight>(0.2, Vector3(1, 4, 4)));

    Vector3 cameraPos{0, 0, 0};

    std::map<std::pair<int, int>, SDL_Color> pixelToColor;

    std::thread t1(findColors, -CANVAS_WIDTH / 2, 0, -CANVAS_HEIGHT / 2, 0, cameraPos, std::ref(pixelToColor));
    std::thread t2(findColors, 0, CANVAS_WIDTH / 2, -CANVAS_HEIGHT / 2, 0, cameraPos, std::ref(pixelToColor));
    std::thread t3(findColors, -CANVAS_WIDTH / 2, 0, 0, CANVAS_HEIGHT / 2, cameraPos, std::ref(pixelToColor));
    std::thread t4(findColors, 0, CANVAS_WIDTH / 2, 0, CANVAS_HEIGHT / 2, cameraPos, std::ref(pixelToColor));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    for (auto itr = pixelToColor.begin(); itr != pixelToColor.end(); ++itr)
    {
        SDL_Color color = itr->second;
        int x = (itr->first).first;
        int y = (itr->first).second;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, x + CANVAS_WIDTH / 2, -y + CANVAS_HEIGHT / 2);
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

void findColors(const int minX, const int maxX, const int minY, const int maxY, const Vector3 cameraPos, std::map<std::pair<int, int>, SDL_Color> &pixelToColor)
{
    for (int x = minX; x < maxX; ++x)
    {
        for (int y = minY; y < maxY; ++y)
        {
            Vector3 direction = canvasToViewport(x, y);
            SDL_Color color = traceRay(cameraPos, direction, 0.001, std::numeric_limits<float>::infinity(), 3);
            pixelToColor.emplace(std::make_pair(x, y), color);
        }
    }
}