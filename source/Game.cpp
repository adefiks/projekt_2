#include "Game.h"
#include "TextureManager.h"
#include "Game_Map.h"
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Timer.h"

Game_Map *game_map;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::isRunning = false;

Manager manager;

// size of camera, same as window
SDL_Rect Game::camera = {0, 0, 1024, 768};
int Game::resolution_width = 1024;
int Game::resolution_height = 768;
int Game::tilesheet_size = 1408;

// player entity
auto &player(manager.addEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    Game::resolution_width = width;
    Game::resolution_height = height;
    Game::camera = {0, 0, width, height}; // update the camera with game resolution

    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Subsystem Initialised!" << endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            cout << "window created!" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "renderer created!" << endl;
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    {
        Timer TimeofThisSection("adding assets");

        game_map = new Game_Map("assets/tilesheet_complete.png", 1, 32);
        game_map->LoadMap("assets/mapa.map", (4096 / 32), (Game::resolution_height / 32));

        cout << "licznik tiles: " << game_map->licznik_tiles << endl;

        player.addComponent<TransformComponent>((Game::resolution_width / 2), (Game::resolution_height / 2), 64, 64, 1);
        player.addComponent<SpriteComponent>("assets/player.png");
        player.addComponent<KeyboardComponent>();
        player.addComponent<GravityComponent>();
        player.addComponent<ColliderComponent>("player");

        player.addGroup(groupPlayer);
    }
}

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayer));
auto &enemies(manager.getGroup(Game::groupEnemy));
auto &colliders(manager.getGroup(Game::groupCollider));

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }
}

void Game::update()
{

    // player collider for detection of collisions
    SDL_Rect player_collider = player.getComponent<ColliderComponent>().collider;

    // player position in this moment for bactracing player
    Vector2D player_position = player.getComponent<TransformComponent>().position;

    // updating and refreshing components
    manager.refresh();

    player.getComponent<KeyboardComponent>().update_first();
    player.getComponent<GravityComponent>().update_first();

    player_collider.x += player.getComponent<TransformComponent>().velocity.x * player.getComponent<TransformComponent>().speed;
    player_collider.y += player.getComponent<TransformComponent>().velocity.y * player.getComponent<TransformComponent>().speed;

    for (auto cc : colliders)
    {
        SDL_Rect c_collider = cc->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(c_collider, player_collider))
        {
            Collision::Collision_action(player.getComponent<TransformComponent>(), player.getComponent<KeyboardComponent>(), player_position, cc->getComponent<ColliderComponent>());
        }
    }

    manager.update();

    // player.getComponent<KeyboardComponent>().jump_reload = false;

    static int counter = 0;
    counter++;
    if (counter == 28)
    {
        cout << " jump active: " << player.getComponent<KeyboardComponent>().jump_reload << endl;
        counter = 0;
    }

    camera.x = player.getComponent<TransformComponent>().position.x - (Game::resolution_width / 2);
    //camera.y = player.getComponent<TransformComponent>().position.y - (Game::resolution_height / 2);

    if (camera.x < 0)
        camera.x = 0;

    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > camera.w * 4)
        camera.x = camera.w;
    if (camera.y > camera.h)
        camera.y = camera.h;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // stuff to render

    for (auto &t : tiles)
    {
        // t->getComponent<TileComponent>().destRect.x;
        if (t->getComponent<TileComponent>().position.x + 32 >= camera.x && t->getComponent<TileComponent>().position.x < camera.x + 1056)
        {
            t->draw();
        }
    }

    for (auto &e : enemies)
    {
        e->draw();
    }

    for (auto &p : players)
    {
        p->draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "game clened!" << endl;
}
