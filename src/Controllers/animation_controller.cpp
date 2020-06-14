#include "animation_controller.h"

int getDX(Direction dir)
{
	if(dir == Direction::LEFT)
		return -1;
	else if(dir == Direction::RIGHT)
		return 1;
	else
		return 0;	
}

// ---AnimationController---
AnimationController::AnimationController(unsigned int _row, unsigned int _framesCount, float _animationSpeed, sf::Vector2f _frameSize, unsigned int _spaceSize, bool _isLooped):
	row(_row), framesCount(_framesCount), spaceSize(_spaceSize), animationSpeed(_animationSpeed), frameSize(_frameSize), isLooped(_isLooped)
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
	if(int(currentFrame) > int(framesCount - 1)) {
		if(isLooped)
			currentFrame = 0;
		else 
			currentFrame = framesCount - 1;
	}
}

sf::IntRect AnimationController::getSpriteRect(Direction direction)
{
	if(direction == Direction::LEFT)
		return sf::IntRect((frameSize.x + spaceSize) * int(getCurrentFrame()) + frameSize.x, (frameSize.y  + spaceSize) * row, -frameSize.x, frameSize.y);
	else
		return sf::IntRect((frameSize.x + spaceSize) * int(getCurrentFrame()), (frameSize.y + spaceSize) * row, frameSize.x, frameSize.y);
}
