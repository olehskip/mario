#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

enum class Direction
{
	LEFT,
	RIGHT
};

class AnimationController
{
public:
	AnimationController(unsigned int _row, unsigned int _framesCount, float _animationSpeed, sf::Vector2f _frameSize, unsigned int _spaceSize);

	const unsigned int row, framesCount, spaceSize;
	const float animationSpeed;
	const sf::Vector2f frameSize;
	
	AnimationController &newObject();

	float getCurrentFrame() const;
	void setCurrentFrame(float frame);

	sf::IntRect getSpriteRect(Direction direction);
private:
	float currentFrame = 0.f;
};
