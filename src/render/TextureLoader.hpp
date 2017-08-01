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

#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include <array>
#include <SDL.h>


class TextureLoader
{
    public:

    enum TextureId
    {
        TEXTURE_PLAYER1 = 0,
        TEXTURE_PLAYER2,
        TEXTURE_PLAYER3,
        TEXTURE_PLAYER4,
        TEXTURE_PROJECTILE,
        NUM_TEXTURES
    };

    TextureLoader();
    ~TextureLoader();
    TextureLoader(const TextureLoader &) = delete;
    TextureLoader & operator=(const TextureLoader &) = delete;

    void loadAllTextures(SDL_Renderer *renderer);
    SDL_Texture* get(TextureId texture);

    private:
    std::array<SDL_Texture*, NUM_TEXTURES> m_loadedTextures;

    void loadTexture(SDL_Renderer *renderer, TextureId texture, const char *imagePath);
};

#endif // TEXTURE_LOADER_HPP
