#include "animated_label_controller.h"
#include <chrono>


AnimatedLabelController::AnimatedLabelController(sf::Vector2f pos, const sf::Font &font, unsigned int fontSize, 
	sf::Color color, const std::string &_finalText, int _delay):
	LabelController(pos, font, fontSize, color, std::string("")), finalText(_finalText), delay(_delay)
{
	std::thread(&AnimatedLabelController::animate, this, finalText).detach();
}

void AnimatedLabelController::animate(std::string finalText)
{
	std::string text = "";
	while(true) {
		if(charCounter > finalText.size() - 1)
			break;
		if(std::find(alphabet.begin(), alphabet.end(), finalText[charCounter]) == alphabet.end()) {
			text += finalText[charCounter];
			std::this_thread::sleep_for(std::chrono::milliseconds(delay * 3));
			setText(text);
			charCounter++;
			alphabetCharCounter = 0;
		}
		else {	
			if(finalText[charCounter] == alphabet[alphabetCharCounter]) {
				text += finalText[charCounter];
				setText(text);
				charCounter++;
				alphabetCharCounter = 0;
			}
			else {
				setText(text + alphabet[alphabetCharCounter]);
				alphabetCharCounter++;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
}
