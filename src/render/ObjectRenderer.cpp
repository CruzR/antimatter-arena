#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include "render/ObjectRenderer.hpp"


ObjectRenderer::ObjectRenderer(TextureLoader & loader)
    :
    m_textureLoader(loader),
    m_zoom(1.0f),
    m_screenRect{0, 0, 960, 540},
    m_cameraOffsetX(0.0f),
    m_cameraOffsetY(0.0f),
    m_drawDebugInformation(false)
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

    drawDebugRect(renderer, &playerRect);
}

void ObjectRenderer::drawDebugRect(SDL_Renderer * renderer, SDL_Rect * rect)
{
    if (m_drawDebugInformation)
    {
        Uint8 tmpR, tmpG, tmpB, tmpA;
        int err = SDL_GetRenderDrawColor(renderer, &tmpR, &tmpG, &tmpB, &tmpA);
        assert(err == 0);

        err = SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        assert(err == 0);

        err = SDL_RenderDrawRect(renderer, rect);
        assert(err == 0);

        err = SDL_SetRenderDrawColor(renderer, tmpR, tmpG, tmpB, tmpA);
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

    drawDebugRect(renderer, &projectileRect);
}

void ObjectRenderer::toScreenCoords(float inX, float inY, int & outX, int & outY)
{
    outX = std::round((inX - m_cameraOffsetX) * 48.0f * m_zoom);
    outY = std::round((inY - m_cameraOffsetY) * 48.0f * m_zoom);
}

int ObjectRenderer::playerSize()
{
    return std::round(128 * m_zoom);
}

int ObjectRenderer::projectileSize()
{
    return std::round(32 * m_zoom);
}

int ObjectRenderer::explosionSize()
{
    return std::round(96 * m_zoom);
}

void ObjectRenderer::zoomToFitGladiators(std::vector<Gladiator> & gladiators)
{
    std::vector<float> positionsX(gladiators.size());
    std::vector<float> positionsY(gladiators.size());

    std::transform(
        gladiators.begin(),
        gladiators.end(),
        positionsX.begin(),
        [](Gladiator & g){ return g.getPositionX(); }
    );

    std::transform(
        gladiators.begin(),
        gladiators.end(),
        positionsY.begin(),
        [](Gladiator & g){ return g.getPositionY(); }
    );

    const float centerX = std::accumulate(
        positionsX.begin(),
        positionsX.end(),
        0.0f
    ) / gladiators.size();

    const float centerY = std::accumulate(
        positionsY.begin(),
        positionsY.end(),
        0.0f
    ) / gladiators.size();

    std::pair<std::vector<float>::iterator, std::vector<float>::iterator> extremaX = std::minmax_element(positionsX.begin(), positionsX.end());
    std::pair<std::vector<float>::iterator, std::vector<float>::iterator> extremaY = std::minmax_element(positionsY.begin(), positionsY.end());

    float bboxX = *extremaX.first - 2.0f;
    float bboxY = *extremaY.first - 2.0f;
    float bboxW = *extremaX.second - bboxX + 2.0f;
    float bboxH = *extremaY.second - bboxY + 2.0f;

    if (bboxH > 0.0f && bboxW > 0.0f)
    {
        if (bboxW / bboxH < 16.0f / 9.0f)
        {
            float newW = bboxH * 16.0f / 9.0f;
            bboxX -= (newW - bboxW) / 2;
            bboxW = newW;
        }
        else if (bboxW / bboxH > 16.0f / 9.0f)
        {
            float newH = bboxW * 9.0f / 16.0f;
            bboxY -= (newH - bboxH) / 2;
            bboxH = newH;
        }

        float newZoom = 960.0f / (bboxW * 48.0f);
        m_cameraOffsetX = bboxX;
        m_cameraOffsetY = bboxY;
        m_zoom = newZoom;
        m_screenRect.w = std::round(960.0f * m_zoom);
        m_screenRect.h = std::round(540.0f * m_zoom);
    }
}

void ObjectRenderer::toggleDrawDebugInformation()
{
    m_drawDebugInformation = !m_drawDebugInformation;
}

void ObjectRenderer::render(SDL_Renderer * renderer, World & world)
{
    for (int i = 0; i < world.getNumProjectiles(); ++i)
    {
        render(renderer, world.getProjectile(i));
    }

    for (int i = 0; i < world.getNumGladiators(); ++i)
    {
        render(renderer, world.getGladiator(i), TextureLoader::TEXTURE_PLAYER1);
    }

    for (int i = 0; i < world.getNumExplosions(); ++i)
    {
        render(renderer, world.getExplosion(i));
    }
}

void ObjectRenderer::render(SDL_Renderer * renderer, const Explosion & explosion)
{
    int screenX, screenY;
    toScreenCoords(explosion.getPositionX(), explosion.getPositionY(), screenX, screenY);

    SDL_Rect explosionRect;
    explosionRect.x = screenX - explosionSize() / 2;
    explosionRect.y = screenY - explosionSize() / 2;
    explosionRect.w = explosionSize();
    explosionRect.h = explosionSize();

    if (rectInScreen(explosionRect, m_screenRect))
    {
        int err = SDL_SetRenderDrawColor(renderer, 223, 113, 38, 255);
        assert(err == 0);

        err = SDL_RenderFillRect(renderer, &explosionRect);

        if (err < 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Rendering Explosion failed: %s", SDL_GetError());
        }
    }

    drawDebugRect(renderer, &explosionRect);
}
