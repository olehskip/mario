#pragma once
#include <array>
#include <vector>
#include <thread>

#include "label_controller.h"


class AnimatedLabelController: public LabelController
{
public:
	AnimatedLabelController(const sf::Font &font, unsigned int fontSize, sf::Color color, const std::string &_finalText, sf::Vector2f pos, int _delay);
	void startAnimation();

	void draw(sf::RenderWindow &window) override;

private:
	void animate();
	std::thread animationThread;

	std::array<char, 26> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
									 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	const std::string finalText;
	std::string text = "";
	unsigned charCounter = 0, alphabetCharCounter = 0;
	const int delay;
};