/*
!!! TransformComponent.h !!!
    * component is responsible for:
        *   position of all entites in game 
        *   velocity of moving entites
*/

#pragma once
#include "Components.h"
#include "Vector2D.h"

// component for position of entity
class TransformComponent : public Component
{
public:
    Vector2D position; // vector 2D for position of entity
    Vector2D velocity; // vector 2D for velocity of entity

    int speed = 3; // speed of entity
    int width;     // width of entity
    int height;    // height of entity
    int scale;     // scaling of entity

    // default constructor zeroing the position
    TransformComponent()
    {
        position.Zero();
    }

    // constructor for scaling the entity
    TransformComponent(int scaleIn)
    {
        position.Zero();

        scale = scaleIn;
    }

    // constructor for puting the x,y on starting position
    TransformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    // constructor for x,y starting position, width,height,scale of entity
    TransformComponent(float x, float y, int h, int w, int scaleIn)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = scaleIn;
    }

    // for init this component (set x,y to 0)
    void init() override
    {
        velocity.Zero();
    }

    // updating the x,y pos in regards of existing velocity and speed
    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};