#include "TextureManager.h"
#include "common.h"

SDL_Texture *TextureManager::LoadTexture(const char *texture)
{
    SDL_Surface *tempSurface = IMG_Load(texture);
    // SDL_SetSurfaceAlphaMod(tempSurface, 10);
    // SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 255, 0, 0));
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
