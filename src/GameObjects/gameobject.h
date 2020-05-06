#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include <memory>


class GameObject
{
public:
	GameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture);
	void update(sf::RenderWindow &window, float time);

	sf::Texture getTextureCopy() const;
	sf::Sprite getSpriteCopy() const;
	void setPosition(sf::Vector2f newPos);
	sf::Vector2f getOffset() const;
	sf::Vector2f getGlobalOffset() const;
	void draw(sf::RenderWindow &window);
	virtual void updateMovement(float time) {};

protected:
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
	sf::Sprite sprite;

	sf::Vector2f offset, globalOffset;
};

class LiveGameObject: public GameObject
{
public:
	LiveGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, sf::Vector2f _accelaration, sf::Vector2f _deceleration, sf::Vector2f _maxAccelaration);
	
	const sf::Vector2f accelaration, deceleration, maxAccelaration;
};

class BotGameObject: public LiveGameObject
{
public:
	BotGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, sf::Vector2f _accelaration, sf::Vector2f _deceleration, sf::Vector2f _maxAccelaration);
	void moveRight(){};
	void moveLeft(){};
	void jump(){};
};
typedef std::shared_ptr<BotGameObject> BotObject_ptr;