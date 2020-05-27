#pragma once
#include <array>
#include <vector>
#include <thread>

#include "label_controller.h"


class AnimatedLabelController: public LabelController
{
public:
	AnimatedLabelController(const std::shared_ptr<sf::Font> font, unsigned int fontSize, sf::Color color, const std::string &_finalText, sf::Vector2f pos, int _delay);
	void startAnimation();

	void draw(sf::RenderWindow &window) override;

private:
	void animate();
	// std::vector<std::thread> animationThreads;
	std::thread animationThread;

	std::array<char, 26> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
									 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	const std::string finalText;
	// std::vector<std::string> texts;
	std::string text = "";
	unsigned charCounter = 0, alphabetCharCounter = 0;
	const int delay;

	std::vector<std::string> split(const std::string &str, const std::string &delim)
	{
		std::vector<std::string> tokens;
		size_t prev = 0, pos = 0;
		do
		{
			pos = str.find(delim, prev);
			if (pos == std::string::npos) pos = str.length();
			std::string token = str.substr(prev, pos-prev);
			if (!token.empty()) tokens.push_back(token);
			prev = pos + delim.length();
		}
		while (pos < str.length() && prev < str.length());
		return tokens;
	}
};