#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

enum class Direction
{
	LEFT,
	RIGHT
};

static int getDX(Direction dir)
{
	if(dir == Direction::LEFT)
		return -1;
	else if(dir == Direction::RIGHT)
		return 1;
	else
		return 0;	
}

class AnimationController
{
public:
	AnimationController(unsigned int _row, unsigned int _framesCount, float _animationSpeed, sf::Vector2f _frameSize, unsigned int _spaceSize, bool _isLooped = false);

	const unsigned int row, framesCount, spaceSize;
	const float animationSpeed;
	const sf::Vector2f frameSize;
	
	AnimationController &newObject();

	float getCurrentFrame() const;
	void setCurrentFrame(float frame);

	sf::IntRect getSpriteRect(Direction direction);

private:
	float currentFrame = 0.f;
	const bool isLooped;
};
