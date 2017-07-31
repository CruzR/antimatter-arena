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
#include "sim/World.hpp"
#include "controller/GladiatorController.hpp"

static TTF_Font *comicNeueTiny;
static TTF_Font *comicNeueMedium;
static TTF_Font *comicNeueHuge;

void initTTF()
{
    int err = TTF_Init();
    assert(err == 0);

    comicNeueTiny = TTF_OpenFont("assets/ComicNeue-Regular.otf", 16);
    assert(comicNeueTiny != nullptr);

    comicNeueMedium = TTF_OpenFont("assets/ComicNeue-Regular.otf", 24);
    assert(comicNeueMedium != nullptr);

    comicNeueHuge = TTF_OpenFont("assets/ComicNeue-Regular.otf", 36);
    assert(comicNeueHuge != nullptr);
}

void teardownTTF()
{
    TTF_CloseFont(comicNeueTiny);
}

SDL_Surface* renderFpsString(int fps, SDL_Rect *rect)
{
    std::ostringstream s;
    s << fps;

    int w, h;

    int err = TTF_SizeUTF8(comicNeueTiny, s.str().c_str(), &w, &h);
    assert(err == 0);

    rect->w = w;
    rect->h = h;
    rect->x = 960 - 5 - w;
    rect->y = 5;

    SDL_Surface *renderedText = TTF_RenderUTF8_Solid(comicNeueTiny, s.str().c_str(), { 255, 255, 255, 255 });

    assert(renderedText != nullptr);

    return renderedText;
}

void renderGladiatorStats(SDL_Renderer * renderer, const Gladiator & glad, int i)
{
    std::ostringstream s;
    s << glad.getHealth() << " HP";
    std::string stats = s.str();

    SDL_Rect rect;
    TTF_SizeUTF8(comicNeueMedium, stats.c_str(), &(rect.w), &(rect.h));
    rect.y = 540 - rect.h - 10;
    rect.x = i * 960 / 4 + (960 / 4 - rect.w) / 2;
    SDL_Color colors[] =
    {
        {172, 50, 50, 255},
        {99, 155, 255, 255},
        {106, 190, 48, 255},
        {251, 242, 54, 255}
    };
    SDL_Surface * surf = TTF_RenderUTF8_Solid(comicNeueMedium, stats.c_str(), colors[glad.getColor()]);
    SDL_Texture * text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);
    SDL_FreeSurface(surf);
}

int main(int argc, char *argv[])
{
    TextureLoader textureLoader;
    World world;

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

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);

    bool gameStarted = false;
    std::vector<GladiatorController> gladiatorControllers;

    bool someoneHasWon = false;
    SDL_Rect victoryLine1Rect{0, 0, 0, 0};
    SDL_Rect victoryLine2Rect{0, 0, 0, 0};
    SDL_Rect instructionsRect{0, 0, 0, 0};
    TTF_SizeUTF8(comicNeueHuge, "VICTORY", &(victoryLine1Rect.w), &(victoryLine1Rect.h));
    TTF_SizeUTF8(comicNeueMedium, "Press any key to exit...", &(victoryLine2Rect.w), &(victoryLine2Rect.h));
    TTF_SizeUTF8(comicNeueMedium, "Insert up to 4 gamepads, then press ENTER to start game.", &(instructionsRect.w), &(instructionsRect.h));
    victoryLine1Rect.y = 20;
    victoryLine1Rect.x = (960 - victoryLine1Rect.w) / 2;
    victoryLine2Rect.y = (540 - victoryLine2Rect.h - 10);
    victoryLine2Rect.x = (960 - victoryLine2Rect.w) / 2;
    instructionsRect.y = (540 - instructionsRect.h) / 2;
    instructionsRect.x = (960 - instructionsRect.w) / 2;
    SDL_Surface *victoryLine1Surface = TTF_RenderUTF8_Blended(comicNeueHuge, "VICTORY", {255, 255, 255, 255});
    SDL_Surface *victoryLine2Surface = TTF_RenderUTF8_Blended(comicNeueMedium, "Press any key to exit...", {255, 255, 255, 255});
    SDL_Surface *instructionsSurface = TTF_RenderUTF8_Blended(comicNeueMedium, "Insert up to 4 gamepads, then press ENTER to start game.", {255, 255, 255, 255});
    SDL_Texture *victoryLine1Texture = SDL_CreateTextureFromSurface(renderer, victoryLine1Surface);
    SDL_Texture *victoryLine2Texture = SDL_CreateTextureFromSurface(renderer, victoryLine2Surface);
    SDL_Texture *instructionsTexture = SDL_CreateTextureFromSurface(renderer, instructionsSurface);
    SDL_FreeSurface(victoryLine1Surface);
    SDL_FreeSurface(victoryLine2Surface);
    SDL_FreeSurface(instructionsSurface);

    while (!shouldQuit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                shouldQuit = true;
            }

            if (event.type == SDL_KEYUP)
            {
                if (!gameStarted)
                {
                    gameStarted = true;

                    int numPlayers = 0;

                    for (int i = 0; i < SDL_NumJoysticks() && numPlayers < 4; ++i)
                    {
                        if (SDL_IsGameController(i))
                        {
                            SDL_GameController *controller = SDL_GameControllerOpen(i);
                            assert(controller != nullptr);
                            int player = world.spawnGladiatorAt(std::cos(numPlayers * M_PI / 2) * 5.0, std::sin(numPlayers * M_PI / 2) * 5.0, static_cast<Gladiator::Color>(numPlayers % static_cast<int>(Gladiator::NUM_COLORS)));
                            gladiatorControllers.emplace_back(world, player, controller);
                            numPlayers += 1;
                        }
                    }

                    while (numPlayers < 4)
                    {
                        int dummy = world.spawnGladiatorAt(std::cos(numPlayers * M_PI / 2) * 5.0, std::sin(numPlayers * M_PI / 2) * 5.0, static_cast<Gladiator::Color>(numPlayers % static_cast<int>(Gladiator::NUM_COLORS)));
                        numPlayers += 1;
                    }
                }

                if (someoneHasWon)
                {
                    shouldQuit = true;
                }

                if (event.key.keysym.scancode == SDL_SCANCODE_F5)
                {
                    objectRenderer.toggleDrawDebugInformation();
                }
            }
        }

        world.tick();

        for (GladiatorController & gladiatorController : gladiatorControllers)
        {
            gladiatorController.update();
        }

        someoneHasWon = gameStarted && world.getNumPlayersAlive() <= 1;

        int framerate = SDL_getFramerate(&fpsManager);
        SDL_Rect fpsRect;
        SDL_Surface *fpsSurface = renderFpsString(framerate, &fpsRect);
        // TODO: SDL docs recommend against using CreateTextureFromSurface each frame.
        SDL_Texture *fpsTexture = SDL_CreateTextureFromSurface(renderer, fpsSurface);
        SDL_FreeSurface(fpsSurface);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        int err = 0;

        objectRenderer.zoomToFitGladiators(world.getGladiators());
        objectRenderer.render(renderer, world);

        if (!gameStarted)
        {
            SDL_RenderCopy(renderer, instructionsTexture, NULL, &instructionsRect);
        }

        if (gameStarted && !someoneHasWon)
        {
            for (int i = 0; i < world.getNumGladiators(); ++i)
            {
                renderGladiatorStats(renderer, world.getGladiator(i), i);
            }
        }

        if (someoneHasWon)
        {
            SDL_RenderCopy(renderer, victoryLine1Texture, NULL, &victoryLine1Rect);
            SDL_RenderCopy(renderer, victoryLine2Texture, NULL, &victoryLine2Rect);
        }

        SDL_RenderCopy(renderer, fpsTexture, NULL, &fpsRect);

        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(fpsTexture);

        SDL_framerateDelay(&fpsManager);
    }

    SDL_DestroyTexture(victoryLine1Texture);
    SDL_DestroyTexture(victoryLine2Texture);
    SDL_DestroyTexture(instructionsTexture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);

    teardownTTF();

    SDL_Quit();

    return 0;
}
