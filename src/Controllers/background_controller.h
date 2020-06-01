#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <array>

#include "../config.h"

class Background
{
public:
	Background(const sf::Texture &mountains, const sf::Texture &forest, const sf::Texture &field);
	void draw(sf::RenderWindow &window);
	
	void setPositionX(float x);
	sf::Vector2f getPosition() const;
	void move(sf::Vector2f pos);

	sf::FloatRect getGlobalBounds() const;

private:
	std::vector<sf::Sprite> backgroundParts;
};

class BackgroundController
{
public:
	BackgroundController(const sf::Texture &mountains, const sf::Texture &forest, const sf::Texture &field);

	void move(sf::Vector2f offset);
	void draw(sf::RenderWindow &window);

private:
	/*
	 * We need 3 sprites because 2 sprites visible, when third sprite becomes the first
	 * It looks like endless background
	 */
	std::array<std::unique_ptr<Background>, 3> backgroundSprites;

	float globalCameraOffsetX = 0.f;
	float spriteWidth;
};