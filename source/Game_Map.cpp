
#include "Game_Map.h"

int Game_Map::licznik_tiles = 0;

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
    int tile_int = 0;
    string tile_string;
    string title_tag = "clear";
    int multiplier = 1;

    // tiles
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            tile_string.clear();
            do
            {
                mapFile.get(tile);
                if (tile != ',')
                    tile_string += tile;

            } while (tile != ',');

            tile_int = atoi(tile_string.c_str());

            if (tile_int != 0)
            {
                tile_int--;
                AddTitle(tile_int, j * (tile_size * map_scale), i * (tile_size * map_scale));
            }

            if (j == (x - 1))
                mapFile.ignore();
        }
    }

    mapFile.ignore();

    // collisions
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            tile_string.clear();
            do
            {
                mapFile.get(tile);
                if (tile != ',')
                    tile_string += tile;

            } while (tile != ',');

            tile_int = atoi(tile_string.c_str());

            if (tile_int != 0)
            {
                switch (tile_int)
                {
                case 1:
                    title_tag = "ground";
                    break;
                case 2:
                    title_tag = "platform";
                    break;
                case 3:
                    title_tag = "water";
                    break;
                default:
                    title_tag = "ground";
                    break;
                }

                auto &tile_collider(manager.addEntity());
                tile_collider.addComponent<ColliderComponent>(title_tag, j * (tile_size * map_scale), i * (tile_size * map_scale), (tile_size * map_scale));
                tile_collider.addGroup(Game::groupCollider);
                // tile_collider.delGroup(Game::groupMap); // TODO ?? not sure if needed
            }

            if (j == (x - 1))
                mapFile.ignore();
        }
    }

    mapFile.close();
}

void Game_Map::LoadMap_colliders(string path, int x, int y)
{
    char tile;
    fstream mapFile;
    mapFile.open(path);

    int src_x, src_y;

    string title_tag = "clear";

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
            case 0:
                title_tag = "clear";
                break;
            case 2:
                title_tag = "platform";
                break;
            case 3:
                title_tag = "water";
                break;
            default:
                title_tag = "water";
                break;
            }
            if (title_tag != "clear")
            {
                auto &tile_collider(manager.addEntity());
                tile_collider.addComponent<ColliderComponent>(title_tag, j * (tile_size * map_scale), i * (tile_size * map_scale), (tile_size * map_scale));
                tile_collider.addGroup(Game::groupCollider);
                tile_collider.delGroup(Game::groupMap); // TODO ?? not sure if needed
            }

            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Game_Map::AddTitle(int tile_int, int x, int y)
{
    int src_x, src_y;
    auto &tile(manager.addEntity());

    int temp_int = tile_int / (Game::tilesheet_size / 32);
    src_y = temp_int * 32;

    src_x = (tile_int - temp_int * (Game::tilesheet_size / 32)) * 32;

    licznik_tiles++;

    tile.addComponent<TileComponent>(src_x, src_y, x, y, tile_size, map_scale, texture);
    tile.addGroup(Game::groupMap);
}