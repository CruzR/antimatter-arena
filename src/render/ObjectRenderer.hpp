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

#ifndef OBJECT_RENDERER_HPP
#define OBJECT_RENDERER_HPP

#include <vector>
#include "SDL.h"
#include "sim/Gladiator.hpp"
#include "sim/Projectile.hpp"
#include "sim/Explosion.hpp"
#include "sim/World.hpp"
#include "render/TextureLoader.hpp"


class ObjectRenderer
{
    public:
    ObjectRenderer(TextureLoader & loader);
    void render(SDL_Renderer * renderer, const Gladiator & gladiator);
    void render(SDL_Renderer * renderer, const Projectile & projectile);
    void render(SDL_Renderer * renderer, const Explosion & explosion);
    void render(SDL_Renderer * renderer, World & world);
    void zoomToFitGladiators(std::vector<Gladiator> & gladiators);
    void toggleDrawDebugInformation();

    private:
    TextureLoader & m_textureLoader;
    float m_zoom;
    SDL_Rect m_screenRect;
    float m_cameraOffsetX;
    float m_cameraOffsetY;
    bool m_drawDebugInformation;

    void toScreenCoords(float inX, float inY, int & outX, int & outY);
    int playerSize();
    int projectileSize();
    int explosionSize();
    void drawDebugRect(SDL_Renderer * renderer, SDL_Rect * rect);
    void renderFloor(SDL_Renderer * renderer);
};

#endif // OBJECT_RENDERER_HPP
