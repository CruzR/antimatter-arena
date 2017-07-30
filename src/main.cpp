#include <cassert>
#include "SDL.h"
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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);

    SDL_Quit();

    return 0;
}
