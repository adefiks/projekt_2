/*
!!! TileComponent.h !!!
    * component is responsible for:
        *  loding the tiles (textures on the map)
        * updating the tiles (position) in regards to camera position
        * drawing the tiles
*/

#pragma once
#include "Components.h"
#include "common.h"

// component for tiles
class TileComponent : public Component
{
private:
    /* data */
public:
    SDL_Texture *texture;       // texture of tile
    SDL_Rect srcRect, destRect; // sorce position and destination position of tile
    Vector2D position;          // vector 2D for tile position

    TileComponent() = default;

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    // constructor with parameters: src_x -> size x of tile, src_y -> size y of tile, x,y -> position of tile in map, tile_scale -> scaling of tile, path -> path to image of tile
    TileComponent(int src_x, int src_y, int x, int y, int tile_size, int tile_scale, const char *path)
    {
        texture = TextureManager::LoadTexture("assets/tilesheet_complete.png");

        position.x = x;
        position.y = y;

        srcRect = {src_x, src_y, tile_size, tile_size};

        destRect = {x, y, tile_size * tile_scale, tile_size * tile_scale};
    }

    // updating position of tile in regards of camera position
    void update() override
    {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }

    // drawing of tiles
    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }
};
