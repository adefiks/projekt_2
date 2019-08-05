/*
!!! Collisions.h !!!
    * class for AABB (Axis-Aligned-Bounding-Box) colissions 
*/

#pragma once
#include "common.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "KeyboardComponent.h"
#include "Vector2D.h"

// Forward declaration
class ColliderComponent;

// class for AABB collisions
class Collision
{
private:
    /* data */
public:
    // Axis-Aligned-Bounding-Box
    static bool AABB(const SDL_Rect &object1, const SDL_Rect &object2);

    //Axis-Aligned-Bounding-Box with Collider Components
    static bool AABB(const ColliderComponent &col1, const ColliderComponent &col2);

    static void Collision_action(TransformComponent &player, KeyboardComponent &keyboard, const Vector2D old_player_position, string collider_tag);
};
