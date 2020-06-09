#include "animated_label_controller.h"
#include <chrono>


AnimatedLabelController::AnimatedLabelController(const sf::Font &font, unsigned int fontSize, 
	sf::Color color, const std::string &_finalText, sf::Vector2f pos, int _delay):
	finalText(_finalText), delay(_delay)
{
	label = std::make_unique<LabelController>(font, fontSize, color, std::string(""), pos);
	std::thread(&AnimatedLabelController::animate, this, finalText).detach();
}

void AnimatedLabelController::draw(sf::RenderWindow &window)
{
	label->draw(window);
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
			label->setText(text);
			charCounter++;
			alphabetCharCounter = 0;
		}
		else {	
			if(finalText[charCounter] == alphabet[alphabetCharCounter]) {
				text += finalText[charCounter];
				label->setText(text);
				charCounter++;
				alphabetCharCounter = 0;
			}
			else {
				label->setText(text + alphabet[alphabetCharCounter]);
				alphabetCharCounter++;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
}
