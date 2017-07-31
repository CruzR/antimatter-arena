#ifndef OBJECT_RENDERER_HPP
#define OBJECT_RENDERER_HPP

#include <vector>
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
    void zoomToFitGladiators(const std::vector<const Gladiator *> & gladiators);
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
    void drawDebugRect(SDL_Renderer * renderer, SDL_Rect * rect);
};

#endif // OBJECT_RENDERER_HPP
