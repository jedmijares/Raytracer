#include "Vector3.h"
#include <SDL2/SDL.h>

const int CANVAS_WIDTH = 640;
const int CANVAS_HEIGHT = 640;

const int VIEWPORT_WIDTH = 6400;
const int VIEWPORT_HEIGHT = 6400;
const int VIEWPORT_DISTANCE = 640;

Vector3 canvasToViewport(int x, int y);
uint32_t traceRay(Vector3 origin, Vector3 direction, float tMin, float tMax);

int main()
{
    //The window we'll be rendering to
    SDL_Window *window = NULL;

    //The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CANVAS_WIDTH, CANVAS_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            //Update the surface
            SDL_UpdateWindowSurface(window);

            //Wait two seconds
            SDL_Delay(2000);
        }
    }

    Vector3 cameraPos{0, 0, 0};
    for (int x = -CANVAS_WIDTH / 2; x < CANVAS_WIDTH / 2; ++x)
    {
        for (int y = -CANVAS_HEIGHT / 2; y < CANVAS_HEIGHT / 2; ++y)
        {
        }
    }

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

Vector3 canvasToViewport(int x, int y)
{
    return Vector3{x * VIEWPORT_WIDTH / CANVAS_WIDTH, y * VIEWPORT_HEIGHT / CANVAS_HEIGHT, VIEWPORT_DISTANCE};
}

uint32_t traceRay(Vector3 origin, Vector3 direction, float tMin, float tMax)
{
}