#include "label_controller.h"

LabelController::LabelController(const sf::Font &font, unsigned int fontSize, sf::Color color, const std::string &text, sf::Vector2f pos)
{
	textObj.setFont(font);
	textObj.setCharacterSize(fontSize);
	textObj.setFillColor(color);
	textObj.setString(text);
	textObj.setPosition(pos);
	textObj.setOrigin(textObj.getLocalBounds().left + textObj.getLocalBounds().width / 2.f, 
					  textObj.getLocalBounds().top + textObj.getLocalBounds().height / 2.f);
}

void LabelController::setText(const std::string &text)
{
	textObj.setString(text);
}

std::string LabelController::getText() const
{
	return textObj.getString();
}

void LabelController::toCenterX(const float windowWidth)
{
	textObj.setPosition(windowWidth / 2.f, textObj.getPosition().y);
}

void LabelController::toCenterY(const float windowHeight)
{
	textObj.setPosition(textObj.getPosition().x, windowHeight / 2.f);
}

void LabelController::toBottomY(const float windowHeight)
{
	textObj.setPosition(0, windowHeight - textObj.getGlobalBounds().height);
}

void LabelController::setPosition(const sf::Vector2f &vector)
{
	textObj.setPosition(vector);
}

void LabelController::blink(bool blinkState, float delay)
{
	if(blinkState)
		blinkingClock.restart();
	isBlinking = blinkState;
	blinkDelay = delay;
}

void LabelController::move(sf::Vector2f pos)
{
	textObj.move(pos);
}

void LabelController::draw(sf::RenderWindow &window)
{
	if(isBlinking) {
		if(blinkingClock.getElapsedTime().asSeconds() > blinkDelay) {
			isVisible = !isVisible;
			blinkingClock.restart();
		}
	}
	else 
		blinkingClock.restart();

	if(isVisible)
		window.draw(textObj);
}
