/*
!!! Animation.h !!!
    * Animation class for sprite component
*/

#pragma once

// Animation class for sprite component
class Animation
{
public:
    int index_x, index_y; // where on image is animation
    int frames;           // how many frames have animation
    int animation_speed;  // how fast the animmation is going

    Animation(int mIndex_x, int mIndex_y, int mFrames, int mAnimation_speed) : index_x(mIndex_x), index_y(mIndex_y), frames(mFrames), animation_speed(mAnimation_speed){};
};
