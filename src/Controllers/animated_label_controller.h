#pragma once
#include <array>
#include <vector>
#include <thread>

#include "label_controller.h"


class AnimatedLabelController: public LabelController
{
public:
	AnimatedLabelController(sf::Vector2f pos, const sf::Font &font, unsigned int fontSize, 
		sf::Color color, const std::string &_finalText, int _delay);

private:
	void animate(std::string finalText);
	const std::string finalText;
	const int delay;

	unsigned charCounter = 0, alphabetCharCounter = 0;
	std::array<char, 26> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
									 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
};
