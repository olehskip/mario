#include "label_controller.h"

LabelController::LabelController(const sf::Font &font, unsigned int fontSize, sf::Color color, const std::string &text, sf::Vector2f pos)
{
	textObj.setFont(font);
	textObj.setCharacterSize(fontSize);
	textObj.setFillColor(color);
	textObj.setString(text);
	textObj.setPosition(pos);
}

void LabelController::setText(const std::string &text)
{
	textObj.setString(text);
}

std::string LabelController::getText() const
{
	return textObj.getString();
}

void LabelController::move(sf::Vector2f pos)
{
	textObj.move(pos);
}

void LabelController::draw(sf::RenderWindow &window)
{
	window.draw(textObj);
}
