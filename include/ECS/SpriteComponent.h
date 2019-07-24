/*
!!! SpriteComponent.h !!!
    * component is responsible for:
        *   loading textures
        *   playing animations
        *   updating animations and position of sprite
*/

#pragma once
#include "Components.h"
#include "common.h"
#include "TextureManager.h"
#include "Animation.h"

// component for sprites
class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    // bool for seting up the animeted sprites

    int frame = 0;
    int animation_speed = 100;

public:
    bool animated = false;
    int animation_index_x = 0;
    int animation_index_y = 0;

    // std map for grouping animations (class) with names of animations
    map<const char *, Animation *> animations;

    SpriteComponent() = default;

    // seting sprite only with parameter -> path (path to texture image)
    SpriteComponent(const char *path)
    {
        setTexture(path);
    }

    // seting sprite with parameter -> path (path to texture image), and animations (now only for player)
    SpriteComponent(const char *path, bool isAnimated)
    {
        animations.emplace("Idle", new Animation(6, 0, 2, 100));
        animations.emplace("Walk_down", new Animation(0, 0, 6, 100));
        animations.emplace("Walk_right", new Animation(0, 1, 6, 100));
        animations.emplace("Walk_up", new Animation(0, 2, 6, 100));
        animations.emplace("Walk_left", new Animation(0, 3, 6, 100));

        this->animated = true;

        play_animation("Idle");

        setTexture(path);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    // seting the texture for sprite
    void setTexture(const char *path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = 0;
        srcRect.y = 0;

        srcRect.h = transform->height;
        srcRect.w = transform->width;
    }

    void update() override
    {

        if (animated)
        {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / animation_speed) % frame) + animation_index_x * transform->width;
        }

        srcRect.y = animation_index_y * transform->height;

        destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    // drawing sprite
    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }

    // playing animations from std map animations
    void play_animation(const char *animation_name)
    {
        this->frame = animations[animation_name]->frames;
        this->animation_index_x = animations[animation_name]->index_x;
        this->animation_index_y = animations[animation_name]->index_y;
        this->animation_speed = animations[animation_name]->animation_speed;
    }
};