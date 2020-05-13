#pragma once

struct AnimationController
{
public:
	AnimationController(unsigned int _row, unsigned int _framesCount);

	const unsigned int row;
	const unsigned int framesCount;
	float currentFrame = 0.f;
	
	AnimationController &newObject();
};
