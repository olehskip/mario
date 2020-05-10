#include "spriteanimationcontroller.h"
#include <iostream>


// ---Animation---
Animation::Animation(unsigned int _row, unsigned int _framesCount):
    row(_row), framesCount(_framesCount)
{

}


SpriteAnimationController::SpriteAnimationController(unsigned int rowsCount, std::vector<unsigned int> framesCounts)
{
    if(rowsCount != framesCounts.size()) {
        std::cout  << "[ERROR] Error with frames counts and rows count" << std::endl;
        return;
    }
    for(int i = 0; i < rowsCount; ++i)
        animations.push_back(Animation(i, framesCounts[i]));
}