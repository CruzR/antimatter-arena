#include <cassert>
#include "SDL.h"
#include "SDL2_framerate.h"
#include "render/TextureLoader.hpp"
#include "sim/Gladiator.hpp"

int main(int argc, char *argv[])
{
    TextureLoader textureLoader;
    Gladiator gladiator;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *mainWindow = SDL_CreateWindow("A game for ludumdare39",
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              960,
                                              480,
                                              0);
    assert(mainWindow != nullptr);

    SDL_Renderer *renderer = SDL_CreateRenderer(mainWindow, -1, 0);

    assert(renderer != nullptr);

    textureLoader.loadAllTextures(renderer);
    gladiator.engageJetpack();

    bool shouldQuit = false;

    FPSmanager fpsManager;
    SDL_initFramerate(&fpsManager);
    SDL_setFramerate(&fpsManager, 60);

    while (!shouldQuit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                shouldQuit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_framerateDelay(&fpsManager);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);

    SDL_Quit();

    return 0;
}
