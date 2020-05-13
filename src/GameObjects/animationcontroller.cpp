#include "animationcontroller.h"


// ---AnimationController---
AnimationController::AnimationController(unsigned int _row, unsigned int _framesCount):
	row(_row), framesCount(_framesCount)
{
}


AnimationController &AnimationController::newObject()
{
	currentFrame = 0.f;
	return *this;
}