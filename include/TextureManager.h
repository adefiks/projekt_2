/*
!!! textureManager.h !!!
    * class used for loading the textures and drawing them into the screen
*/

#pragma once
#include "game.h"

// class used for loading the textures and drawing them into the screen
class TextureManager
{
public:
  // loading the texture with the parameter -> fileName (path to texture image)
  static SDL_Texture *LoadTexture(const char *fileName);

  // method for drawing the texture with the parameters -> tex (SDL_texture to draw), sorce dimension (x,y,h,w), destination dimension (x,y,h,w)
  static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
};
