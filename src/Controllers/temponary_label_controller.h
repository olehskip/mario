#pragma once
#include "label_controller.h"


class TemponaryLabelController: public LabelController
{
public:
	TemponaryLabelController(sf::Vector2f pos, const sf::Font &font, unsigned int fontSize, 
		sf::Color color, const std::string &_text, float _visibleTime);

	void draw(sf::RenderWindow &window) override;
	void update();
	void show(const std::string &text);

private:
	bool mIsVisible = false;
	const float visibleTime;
	sf::Clock hideClock;
};