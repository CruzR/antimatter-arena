#ifndef OBJECT_RENDERER_HPP
#define OBJECT_RENDERER_HPP

#include "SDL.h"
#include "sim/Gladiator.hpp"
#include "sim/Projectile.hpp"
#include "render/TextureLoader.hpp"


class ObjectRenderer
{
    public:
    ObjectRenderer(TextureLoader & loader);
    void render(SDL_Renderer * renderer, const Gladiator & gladiator, TextureLoader::TextureId texture);
    void render(SDL_Renderer * renderer, const Projectile & projectile);

    private:
    TextureLoader & m_textureLoader;
    float m_zoom;
    SDL_Rect m_screenRect;

    void toScreenCoords(float inX, float inY, int & outX, int & outY);
    int playerSize();
    int projectileSize();
};

#endif // OBJECT_RENDERER_HPP
