#include "temponary_label_controller.h"

TemponaryLabelController::TemponaryLabelController(const sf::Font &font, unsigned int fontSize, 
	sf::Color color, const std::string &_text, sf::Vector2f pos, float _visibleTime):
	LabelController(font, fontSize, color, _text, pos), visibleTime(_visibleTime)
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
