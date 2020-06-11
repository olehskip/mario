#pragma once
#include "label_controller.h"


class TemponaryLabelController: public LabelController
{
public:
	TemponaryLabelController(const sf::Font &font, unsigned int fontSize, 
		sf::Color color, const std::string &_text, sf::Vector2f pos, float _visibleTime);

	void draw(sf::RenderWindow &window);
	void update();
	void show(const std::string &text);

private:
	bool mIsVisible = false;
	const float visibleTime;
	sf::Clock hideClock;
};