#include <algorithm>
#include <cassert>
#include <cmath>
#include <sstream>
#include <vector>
#include "SDL.h"
#include "SDL2_framerate.h"
#include "SDL_ttf.h"
#include "render/TextureLoader.hpp"
#include "render/ObjectRenderer.hpp"
#include "sim/Gladiator.hpp"
#include "sim/Projectile.hpp"
#include "controller/GladiatorController.hpp"

static TTF_Font *comicNeue;

void initTTF()
{
    int err = TTF_Init();
    assert(err == 0);

    comicNeue = TTF_OpenFont("assets/ComicNeue-Regular.otf", 16);
    assert(comicNeue != nullptr);
}

void teardownTTF()
{
    TTF_CloseFont(comicNeue);
}

SDL_Surface* renderFpsString(int fps, SDL_Rect *rect)
{
    std::ostringstream s;
    s << fps;

    int w, h;

    int err = TTF_SizeUTF8(comicNeue, s.str().c_str(), &w, &h);
    assert(err == 0);

    rect->w = w;
    rect->h = h;
    rect->x = 960 - 5 - w;
    rect->y = 5;

    SDL_Surface *renderedText = TTF_RenderUTF8_Solid(comicNeue, s.str().c_str(), { 255, 255, 255, 255 });

    assert(renderedText != nullptr);

    return renderedText;
}

int main(int argc, char *argv[])
{
    TextureLoader textureLoader;
    Gladiator gladiator;
    Gladiator bot;
    std::vector<const Gladiator *> gladiators{&gladiator, &bot};
    Projectile projectile;
    projectile.setMoveDirection(45.0f);

    SDL_Init(SDL_INIT_EVERYTHING);

    initTTF();

    SDL_Window *mainWindow = SDL_CreateWindow("A game for ludumdare39",
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              960,
                                              540,
                                              0);
    assert(mainWindow != nullptr);

    SDL_Renderer *renderer = SDL_CreateRenderer(mainWindow, -1, 0);

    assert(renderer != nullptr);

    textureLoader.loadAllTextures(renderer);

    ObjectRenderer objectRenderer(textureLoader);

    bool shouldQuit = false;

    FPSmanager fpsManager;
    SDL_initFramerate(&fpsManager);
    SDL_setFramerate(&fpsManager, 60);

    SDL_Rect playerRect = { 0, 0, 128, 128 };
    SDL_Rect projectileRect = { 128, 48, 32, 32 };

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);

    SDL_GameController *controller = nullptr;
    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
        {
            controller = SDL_GameControllerOpen(i);
            assert(controller != nullptr);
            break;
        }
    }
    assert(controller != nullptr);

    GladiatorController gladiatorController(gladiator, controller);

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

        gladiatorController.update();
        gladiator.tick();
        bot.tick();

        projectile.tick();

        int framerate = SDL_getFramerate(&fpsManager);
        SDL_Rect fpsRect;
        SDL_Surface *fpsSurface = renderFpsString(framerate, &fpsRect);
        // TODO: SDL docs recommend against using CreateTextureFromSurface each frame.
        SDL_Texture *fpsTexture = SDL_CreateTextureFromSurface(renderer, fpsSurface);
        SDL_FreeSurface(fpsSurface);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        int err = 0;

        objectRenderer.zoomToFitGladiators(gladiators);
        objectRenderer.render(renderer, gladiator, TextureLoader::TEXTURE_PLAYER1);
        objectRenderer.render(renderer, bot, TextureLoader::TEXTURE_PLAYER2);
        objectRenderer.render(renderer, projectile);

        SDL_RenderCopy(renderer, fpsTexture, NULL, &fpsRect);

        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(fpsTexture);

        SDL_framerateDelay(&fpsManager);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);

    teardownTTF();

    SDL_Quit();

    return 0;
}
