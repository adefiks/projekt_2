/*
!!! ColliderComponent.h !!!
    * componet for storing the position and name of collider (for next usage) 
*/

#pragma once
#include "common.h"
#include "Components.h"

//  componet for storing the position and name of collider
class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    string tag;

    TransformComponent *transform;

    // constructor with the name parameter
    ColliderComponent(string t)
    {
        tag = t;
    }

    // constructor with the name parameter and collider size
    ColliderComponent(string t, int x, int y, int size)
    {
        tag = t;
        collider = {x, y, size, size};
    }

    // initialize of collider -> check if it have transform component if not create
    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
    }

    // update of collider
    void update() override
    {
        if (tag != "ground" && tag != "grass" && tag != "dirt")
        {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }
    }
};
