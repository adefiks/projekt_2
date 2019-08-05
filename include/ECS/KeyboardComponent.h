/*
!!! KeyboardComponent.h !!!
    * component is responsible for:
        *   keyboard input
        *   playing animations
*/

#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

// keyboard input
class KeyboardComponent : public Component
{
private:
    // timer for space key (falling time)
    int space_timer = 0;

public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    // is jump active
    bool jump_active = false;

    // jumping reloading (when touching ground)
    bool jump_reload = true;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_SPACE:
                if (jump_reload)
                {
                    jump_active = true;
                    jump_reload = false;
                    if (sprite->animated)
                        sprite->play_animation("jump");
                }
                break;
            case SDLK_s: // duck and cover !
                // transform->velocity.y = 1;
                if (sprite->animated)
                    sprite->play_animation("Walk_down");
                break;
            case SDLK_a:
                transform->velocity.x = -1;
                if (sprite->animated)
                    sprite->play_animation("Walk_left");
                break;
            case SDLK_d:
                transform->velocity.x = 1;
                if (sprite->animated)
                    sprite->play_animation("Walk_right");
                break;
            case SDLK_ESCAPE:
                Game::isRunning = false;
            default:
                break;
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                // transform->velocity.y = 0;
                // if (sprite->animated)
                //     sprite->play_animation("Idle");
                break;
            case SDLK_s:
                // transform->velocity.y = 0;
                // if (sprite->animated)
                //     sprite->play_animation("Idle");
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                if (sprite->animated)
                    sprite->play_animation("Idle");
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                if (sprite->animated)
                    sprite->play_animation("Idle");
                break;
            default:
                break;
            }
        }

        if (jump_active)
            space_timer++;

        if (space_timer == 28)
        {
            space_timer = 0;
            jump_active = false;
        }
    }
};
