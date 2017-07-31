#include <cmath>
#include "render/ObjectRenderer.hpp"


ObjectRenderer::ObjectRenderer(TextureLoader & loader)
    :
    m_textureLoader(loader),
    m_zoom(1.0f),
    m_screenRect{0, 0, 960, 540}
{
}

static const int PLAYER_SIZE = 128;
static const int PROJECTILE_SIZE = 32;

static bool rectInScreen(SDL_Rect & rect, SDL_Rect screenRect)
{
    return (rect.x >= screenRect.x && rect.x < screenRect.x + screenRect.w && rect.y >= screenRect.y && rect.y < screenRect.y + screenRect.h)
        || (rect.x >= screenRect.x && rect.x < screenRect.x + screenRect.w && rect.y + rect.h >= screenRect.y && rect.y + rect.h < screenRect.y + screenRect.h)
        || (rect.x + rect.w >= screenRect.x && rect.x + rect.w < screenRect.x + screenRect.w && rect.y >= screenRect.y && rect.y < screenRect.y + screenRect.h)
        || (rect.x + rect.w >= screenRect.x && rect.x + rect.w < screenRect.x + screenRect.w && rect.y + rect.h >= screenRect.y && rect.y + rect.h < screenRect.y + screenRect.h);
}

void ObjectRenderer::render(SDL_Renderer *renderer, const Gladiator & gladiator, TextureLoader::TextureId texture)
{
    int screenX, screenY;
    toScreenCoords(gladiator.getPositionX(), gladiator.getPositionY(), screenX, screenY);

    SDL_Rect playerRect;
    playerRect.x = screenX - playerSize() / 2;
    playerRect.y = screenY - playerSize() / 2;
    playerRect.w = playerSize();
    playerRect.h = playerSize();

    if (rectInScreen(playerRect, m_screenRect))
    {
        int err = SDL_RenderCopyEx(
            renderer,
            m_textureLoader.get(texture),
            NULL,
            &playerRect,
            gladiator.getAimDirection(),
            NULL,
            SDL_FLIP_NONE
        );

        if (err < 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Rendering Gladiator failed: %s", SDL_GetError());
        }
    }
}

void ObjectRenderer::render(SDL_Renderer * renderer, const Projectile & projectile)
{
    int screenX, screenY;
    toScreenCoords(projectile.getPositionX(), projectile.getPositionY(), screenX, screenY);

    SDL_Rect projectileRect;
    projectileRect.x = screenX - projectileSize() / 2;
    projectileRect.y = screenY - projectileSize() / 2;
    projectileRect.w = projectileSize();
    projectileRect.h = projectileSize();

    if (rectInScreen(projectileRect, m_screenRect))
    {
        int err = SDL_RenderCopyEx(
            renderer,
            m_textureLoader.get(TextureLoader::TEXTURE_PROJECTILE),
            NULL,
            &projectileRect,
            projectile.getMoveDirection(),
            NULL,
            SDL_FLIP_NONE
        );

        if (err < 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Rendering Projectile failed: %s", SDL_GetError());
        }
    }
}

void ObjectRenderer::toScreenCoords(float inX, float inY, int & outX, int & outY)
{
    outX = std::round(inX * 48.0f * m_zoom);
    outY = std::round(inY * 48.0f * m_zoom);
}

int ObjectRenderer::playerSize()
{
    return std::round(128 * m_zoom);
}

int ObjectRenderer::projectileSize()
{
    return std::round(32 * m_zoom);
}
