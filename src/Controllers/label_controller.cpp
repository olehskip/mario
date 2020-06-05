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

void LabelController::centerX(const float windowCenterX)
{
	textObj.setOrigin(textObj.getLocalBounds().left + textObj.getLocalBounds().width / 2.f, textObj.getOrigin().y);
	textObj.setPosition(windowCenterX / 2.f, textObj.getPosition().y);
}

void LabelController::centerY(const float windowCenterY)
{
	textObj.setOrigin(textObj.getOrigin().x, textObj.getLocalBounds().top + textObj.getLocalBounds().height / 2.f);
	textObj.setPosition(textObj.getPosition().x, windowCenterY / 2.f);
}

void LabelController::blink(bool blinkState)
{
	if(blinkState)
		blinkingClock.restart();
	isBlinking = blinkState;
}

void LabelController::move(sf::Vector2f pos)
{
	textObj.move(pos);
}

void LabelController::draw(sf::RenderWindow &window)
{
	if(isBlinking) {
		if(blinkingClock.getElapsedTime().asSeconds() > 0.4f) {
			isVisible = !isVisible;
			blinkingClock.restart();
		}
	}
	else 
		blinkingClock.restart();

	if(isVisible)
		window.draw(textObj);
}
