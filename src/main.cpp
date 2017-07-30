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

    SDL_Rect playerRect = { 0, 0, 128, 128 };
    SDL_Rect projectileRect = { 128, 48, 32, 32 };

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);

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
        int err = 0;
        err = SDL_RenderCopy(renderer, textureLoader.get(TextureLoader::TEXTURE_PLAYER), NULL, &playerRect);
        if (err < 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "RenderCopy(%p) failed: %s", textureLoader.get(TextureLoader::TEXTURE_PLAYER), SDL_GetError());
        }

        err = SDL_RenderCopy(renderer, textureLoader.get(TextureLoader::TEXTURE_PROJECTILE), NULL, &projectileRect);
        if (err < 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "RenderCopy(%p) failed: %s", textureLoader.get(TextureLoader::TEXTURE_PROJECTILE), SDL_GetError());
        }

        SDL_RenderPresent(renderer);

        SDL_framerateDelay(&fpsManager);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);

    SDL_Quit();

    return 0;
}
