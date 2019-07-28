#pragma once

#include "ECS.h"
#include "Components.h"

class GravityComponent : public Component
{
private:
    /* data */
public:
    TransformComponent *transform;
    bool jump_active;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        jump_active = &entity->getComponent<KeyboardComponent>().jump_active;

        if (jump_active)
        {
            transform->velocity.y = -2;
        }
        else
        {
            transform->velocity.y = 1;
        }
    }
};
