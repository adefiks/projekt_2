#include "Gameobject.h"
#include "TextureManager.h"

Gameobject::Gameobject(const char *textureSheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(textureSheet);

    xpos = x;
    ypos = y;
}

Gameobject::~Gameobject()
{
}

void Gameobject::Update()
{
    xpos++;
    ypos++;

    srcRect.h = 64;
    srcRect.w = 64;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.h = srcRect.h * 2;
    destRect.w = srcRect.w * 2;
}

void Gameobject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}