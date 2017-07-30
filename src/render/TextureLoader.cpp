#include <cassert>
#include "SDL_image.h"
#include "render/TextureLoader.hpp"


void TextureLoader::loadAllTextures(SDL_Renderer *renderer)
{
    const int availableLoaders = IMG_Init(IMG_INIT_PNG);
    assert((availableLoaders & IMG_INIT_PNG) != 0);

    loadTexture(renderer, TEXTURE_PLAYER, "assets/player.png");
    loadTexture(renderer, TEXTURE_PROJECTILE, "assets/projectile.png");
}

void TextureLoader::loadTexture(SDL_Renderer *renderer, TextureId texture, const char *imagePath)
{
    SDL_Surface *imageSurface = IMG_Load(imagePath);
    assert(imageSurface != 0);

    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    assert(imageTexture != 0);

    SDL_FreeSurface(imageSurface);
}

SDL_Texture* TextureLoader::get(TextureId texture)
{
    return m_loadedTextures.at(texture);
}

TextureLoader::TextureLoader()
{
    for (SDL_Texture*& texture : m_loadedTextures)
    {
        texture = nullptr;
    }
}

TextureLoader::~TextureLoader()
{
    for (SDL_Texture*& texture : m_loadedTextures)
    {
        if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
}
