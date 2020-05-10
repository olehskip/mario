#pragma once

#include <vector>

struct Animation
{
public:
    Animation(unsigned int _row, unsigned int _framesCount);

    const unsigned int row;
    const unsigned int framesCount;
    unsigned int currentFrame;
};

class SpriteAnimationController
{
public:
    SpriteAnimationController(unsigned int rowsCount, std::vector<unsigned int> framesCounts);

private:
    std::vector<Animation> animations;

};