#include "animated_label_controller.h"
#include <iostream>
#include <chrono>

AnimatedLabelController::AnimatedLabelController(const std::shared_ptr<sf::Font> font, unsigned int fontSize, sf::Color color, const std::string &_finalText, sf::Vector2f pos, int _delay):
	LabelController(font, fontSize, color, std::string(""), pos), finalText(_finalText), delay(_delay)
{
	animationThread = std::thread(&AnimatedLabelController::animate, this);
	// textObj.setString("pasasi");
}

void AnimatedLabelController::startAnimation()
{
	static bool isAlreadyStarted;
	if(!isAlreadyStarted) {
		isAlreadyStarted = true;
		animationThread.detach();
	}
}

void AnimatedLabelController::draw(sf::RenderWindow &window) // override
{
	startAnimation();
	LabelController::draw(window);
}

void AnimatedLabelController::animate()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	while(true) {
		if(charCounter > finalText.size() - 1)
			break;
		if(std::find(alphabet.begin(), alphabet.end(), finalText[charCounter]) == alphabet.end()) {
			text += finalText[charCounter];
			std::this_thread::sleep_for(std::chrono::milliseconds(delay * 3));
			textObj.setString(text);
			charCounter++;
			alphabetCharCounter = 0;
		}
		else {	
			if(finalText[charCounter] == alphabet[alphabetCharCounter]) {
				text += finalText[charCounter];
				textObj.setString(text);
				charCounter++;
				alphabetCharCounter = 0;
			}
			else {
				textObj.setString(text + alphabet[alphabetCharCounter]);
				alphabetCharCounter++;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
}