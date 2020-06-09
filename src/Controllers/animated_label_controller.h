#pragma once
#include <array>
#include <vector>
#include <thread>

#include "label_controller.h"


class AnimatedLabelController
{
public:
	AnimatedLabelController(const sf::Font &font, unsigned int fontSize, 
		sf::Color color, const std::string &_finalText, sf::Vector2f pos, int _delay);

	void draw(sf::RenderWindow &window);

private:
	void animate(std::string finalText);
	const std::string finalText;
	const int delay;
	std::unique_ptr<LabelController> label;

	unsigned charCounter = 0, alphabetCharCounter = 0;
	std::array<char, 26> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
									 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
};
