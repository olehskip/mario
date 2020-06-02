#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <memory>


class GameObject
{
public:
	GameObject(sf::Vector2f pos, sf::Vector2f _scale, const sf::Texture &_texture);

	sf::Sprite getSpriteCopy() {return sprite;}
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	void setPosition(sf::Vector2f newPos);
	sf::Vector2f getOffset() const;
	
	void draw(sf::RenderWindow &window);
	virtual void updateMovement(float deltaTime) {};


protected:
	const sf::Texture &texture;
	sf::Sprite sprite;

	sf::Vector2f offset = sf::Vector2f(0, 0);
};


// class BotGameObject: public GameObject
// {
// public:
// 	BotGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, sf::Vector2f _acceleration, sf::Vector2f _deceleration, sf::Vector2f _maxAcceleration);
// 	void moveRight(){};
// 	void moveLeft(){};
// 	void jump(){};
// };
// typedef std::shared_ptr<BotGameObject> BotObject_ptr;