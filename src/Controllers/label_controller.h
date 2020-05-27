#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include <memory>


class LabelController
{
public:
	LabelController(const std::shared_ptr<sf::Font> font, unsigned int fontSize, sf::Color color, const std::string &text, sf::Vector2f pos);
	void setText(const std::string &text);
	std::string getText() const;
	
	void move(sf::Vector2f pos);

	virtual void draw(sf::RenderWindow &window);

protected:
	sf::Text textObj;
};