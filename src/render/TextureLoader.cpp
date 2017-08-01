/*
 * Copyright 2017 Thomas Glamsch
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cassert>
#include "SDL_image.h"
#include "render/TextureLoader.hpp"


void TextureLoader::loadAllTextures(SDL_Renderer *renderer)
{
    const int availableLoaders = IMG_Init(IMG_INIT_PNG);
    assert((availableLoaders & IMG_INIT_PNG) != 0);

    loadTexture(renderer, TEXTURE_PLAYER1, "assets/player1.png");
    loadTexture(renderer, TEXTURE_PLAYER2, "assets/player2.png");
    loadTexture(renderer, TEXTURE_PLAYER3, "assets/player3.png");
    loadTexture(renderer, TEXTURE_PLAYER4, "assets/player4.png");
    loadTexture(renderer, TEXTURE_PROJECTILE, "assets/projectile.png");
}

void TextureLoader::loadTexture(SDL_Renderer *renderer, TextureId texture, const char *imagePath)
{
    SDL_Surface *imageSurface = IMG_Load(imagePath);
    assert(imageSurface != 0);

    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    assert(imageTexture != 0);

    SDL_FreeSurface(imageSurface);

    m_loadedTextures.at(texture) = imageTexture;
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
