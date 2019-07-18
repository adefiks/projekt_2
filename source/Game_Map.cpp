
#include "Game_Map.h"

Game_Map::Game_Map(const char *imap_file, int imap_scale, int itile_size) : map_file(imap_file), map_scale(imap_scale), tile_size(itile_size)
{
}

Game_Map::~Game_Map()
{
}

void Game_Map::LoadMap(string path, int x, int y)
{
    char tile;
    fstream mapFile;
    mapFile.open(path);

    int src_x, src_y;

    string title_tag = "water";

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            mapFile.get(tile);
            src_y = atoi(&tile) * tile_size;
            mapFile.get(tile);
            src_x = (atoi(&tile) - 1) * tile_size;

            switch (atoi(&tile))
            {
            case 1:
                title_tag = "dirt";
                break;
            case 2:
                title_tag = "grass";
                break;
            case 3:
                title_tag = "water";
                break;
            default:
                title_tag = "water";
                break;
            }

            // if (atoi(&tile) == 3)
            // {
            auto &tile_collider(manager.addEntity());
            tile_collider.addComponent<ColliderComponent>(title_tag, j * (tile_size * map_scale), i * (tile_size * map_scale), (tile_size * map_scale));
            tile_collider.addGroup(Game::groupCollider);
            // }

            AddTitle(src_x, src_y, j * (tile_size * map_scale), i * (tile_size * map_scale));

            mapFile.ignore();
        }
    }

    mapFile.close();
}

void Game_Map::AddTitle(int src_x, int src_y, int x, int y)
{
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(src_x, src_y, x, y, tile_size, map_scale, map_file);
    tile.addGroup(Game::groupMap);
}