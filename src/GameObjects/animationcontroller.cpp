#include "animationcontroller.h"


// ---AnimationController---
AnimationController::AnimationController(unsigned int _row, unsigned int _framesCount, float _animationSpeed):
	row(_row), framesCount(_framesCount), animationSpeed(_animationSpeed)
{
}


AnimationController &AnimationController::newObject()
{
	currentFrame = 0.f;
	return *this;
}

float AnimationController::getCurrentFrame() const
{
	return currentFrame;
}

void AnimationController::setCurrentFrame(float frame)
{
	currentFrame = frame;
	if(int(currentFrame) >= framesCount)
		currentFrame = framesCount - 1;
}
