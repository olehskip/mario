#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <memory>


class GameObject
{
public:
	GameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture);
	sf::Sprite getSpriteCopy();
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	void setPosition(sf::Vector2f newPos);
	sf::Vector2f getOffset() const;
	void setOffset(sf::Vector2f newOffset);
	
	void draw(sf::RenderWindow &window);
	virtual void updateMovement(float deltaTime) = 0;

	bool isStandingOnAnyBlock = false;
	bool isNeedToRemove() const;

	friend bool operator==(const GameObject& left, const GameObject& right)
	{
		return left.getOffset() == right.getOffset() &&
			left.isNeedToRemove() == right.isNeedToRemove() &&
			left.getPosition() == right.getPosition() &&
			left.getGlobalBounds() == right.getGlobalBounds();
	}

protected:
	const sf::Texture &texture;
	sf::Sprite sprite;
	bool mIsNeedToRemove = false;

	sf::Vector2f offset = sf::Vector2f(0, 0);
};
