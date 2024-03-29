#include "Collision.h"

bool Collision::AABB(const SDL_Rect &object1, const SDL_Rect &object2)
{
    if (object1.x + object1.w >= object2.x &&
        object2.x + object2.w >= object1.x &&
        object1.y + object1.h >= object2.y &&
        object2.y + object2.h >= object1.y)
    {
        return true;
    }

    return false;
}

bool Collision::AABB(const ColliderComponent &object1, const ColliderComponent &object2)
{
    if (AABB(object1.collider, object2.collider))
    {
        cout << object1.tag << " hit: " << object2.tag << endl;
        return true;
    }

    return false;
}

void Collision::Collision_action(TransformComponent &player, KeyboardComponent &keyboard, const Vector2D old_player_position, ColliderComponent &collider_object)
{
    if (collider_object.tag == "ground")
    {
        if (collider_object.collider.y < player.position.y + player.height)
        {
            player.velocity.x = 0;
        }

        player.velocity.y = 0;

        keyboard.jump_reload = true;
        keyboard.jump_active = false;

        player.position = old_player_position;
    }
    else if (collider_object.tag == "grass")
    {
        player.speed = 3;
    }
    else if (collider_object.tag == "dirt")
    {
        player.speed = 1;
    }
    else if (collider_object.tag == "stone")
    {
        player.position = old_player_position;
    }
}