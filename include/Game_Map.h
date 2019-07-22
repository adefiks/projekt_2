/*
!!! Game_Map.h !!!
    * class for:
        * loading maps 
        * adding titles to maps 
*/

#pragma once
#include "common.h"
#include "Game.h"
#include "ECS.h"
#include "Components.h"

extern Manager manager;

class Game_Map
{
private:
    // map image to open (image of tiles)
    const char *map_file;

    // scaling of map (for tiles)
    int map_scale;

    // size of tiles (int his case 32x32)
    int tile_size;

    // texture of tile
    SDL_Texture *texture = TextureManager::LoadTexture("assets/tilesheet_complete.png");

public:
    Game_Map(const char *imap_file, int imap_scale, int itile_size);
    ~Game_Map();

    // loading map from txt file, x,y -> size of map in tiles
    void LoadMap(string path, int x, int y);

    // loading colliders for game map, x,y -> size of map in tiles
    void LoadMap_colliders(string path, int x, int y);

    // adding tiles to map
    void AddTitle(int tile_int, int x, int y);

    static int licznik_tiles;
};
