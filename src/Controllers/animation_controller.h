#pragma once

class AnimationController
{
public:
	AnimationController(unsigned int _row, unsigned int _framesCount, float _animationSpeed);

	const unsigned int row;
	const unsigned int framesCount;
	const float animationSpeed;
	
	AnimationController &newObject();

	float getCurrentFrame() const;
	void setCurrentFrame(float frame);

private:
	float currentFrame = 0.f;
};
