#include "Game.h"
#include "TextureManager.h"
#include "Game_Map.h"
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Game_Map *game_map;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::isRunning = false;

Manager manager;

// size of camera, same as window
SDL_Rect Game::camera = {0, 0, 800, 640};

// player entity
auto &player(manager.addEntity());

// stone entity
auto &stone(manager.addEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
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

    game_map = new Game_Map("assets/tiles.png", 2, 32);
    game_map->LoadMap("assets/map2.map", 25, 20);

    stone.addComponent<TransformComponent>(140, 320, 32, 32, 4);
    stone.addComponent<SpriteComponent>("assets/large_rock.png");
    stone.addComponent<ColliderComponent>("stone");
    stone.addGroup(groupMap);
    stone.addGroup(groupCollider);

    player.addComponent<TransformComponent>(400, 320, 64, 64, 2);
    player.addComponent<SpriteComponent>("assets/goblin.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayer);
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

    manager.refresh();
    manager.update();

    for (auto cc : colliders)
    {
        SDL_Rect c_collider = cc->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(c_collider, player_collider))
        {
            Collision::Collision_action(player.getComponent<TransformComponent>(), player_position, cc->getComponent<ColliderComponent>().tag);
            // player.getComponent<TransformComponent>().position = player_position;
        }
    }

    cout << " Player speed: " << player.getComponent<TransformComponent>().speed << endl;

    player.getComponent<TransformComponent>().speed;
    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    if (camera.x < 0)
        camera.x = 0;

    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > camera.w)
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
        t->draw();
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
