#include "animation_controller.h"


// ---AnimationController---
AnimationController::AnimationController(unsigned int _row, unsigned int _framesCount, float _animationSpeed, sf::Vector2f _frameSize, unsigned int _spaceSize):
	row(_row), framesCount(_framesCount), animationSpeed(_animationSpeed), frameSize(_frameSize), spaceSize(_spaceSize)
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
	if(int(currentFrame) > framesCount - 1)
		currentFrame = framesCount - 1;
}

sf::IntRect AnimationController::getSpriteRect(Direction direction)
{
	if(direction == Direction::LEFT)
		return sf::IntRect((frameSize.x + spaceSize) * int(getCurrentFrame()) + frameSize.x, (frameSize.y  + spaceSize) * row, -frameSize.x, frameSize.y);
	else
		return sf::IntRect((frameSize.x + spaceSize) * int(getCurrentFrame()), (frameSize.y + spaceSize) * row, frameSize.x, frameSize.y);
}
