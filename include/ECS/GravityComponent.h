#pragma once

#include "ECS.h"
#include "Components.h"

class GravityComponent : public Component
{
private:
    /* data */
public:
    TransformComponent *transform;
    KeyboardComponent *keyboard;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        keyboard = &entity->getComponent<KeyboardComponent>();
    }

    void update_first()
    {
        if (keyboard->jump_active)
        {
            transform->velocity.y = -3;
        }
        else
        {
            keyboard->jump_reload = false;
            transform->velocity.y = 2;
        }
    }

    // void update() override
    // {
    //     // if (keyboard->jump_active)
    //     // {
    //     //     transform->velocity.y = -3;
    //     // }
    //     // else
    //     // {
    //     //     transform->velocity.y = 1;
    //     // }
    // }
};
