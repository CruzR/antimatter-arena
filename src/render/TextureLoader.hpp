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
