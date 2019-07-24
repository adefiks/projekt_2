#pragma once

#include "ECS.h"
#include "Components.h"

class GravityComponent : public Component
{
private:
    /* data */
public:
    TransformComponent *transform;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        transform->velocity.y = 1;
    }
};
