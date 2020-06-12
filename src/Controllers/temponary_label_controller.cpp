#include "temponary_label_controller.h"

TemponaryLabelController::TemponaryLabelController(sf::Vector2f pos, const sf::Font &font, unsigned int fontSize, 
	sf::Color color, const std::string &_text, float _visibleTime):
	LabelController(pos, font, fontSize, color, _text), visibleTime(_visibleTime)
{

}

void TemponaryLabelController::draw(sf::RenderWindow &window)
{
	if(isVisible)
		LabelController::draw(window);
}

void TemponaryLabelController::update()
{
	if(hideClock.getElapsedTime().asSeconds() > visibleTime)
		isVisible = false;
}

void TemponaryLabelController::show(const std::string &text)
{
	hideClock.restart();
	isVisible = true;
	setText(text);
}
