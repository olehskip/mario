#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <thread>
#include <atomic>

#include "label_controller.h"


class GameOverSceneController
{
public:
	GameOverSceneController(const sf::Font &font);
	~GameOverSceneController();

	void draw(sf::RenderWindow &window);
	void setShowState(bool state);

private:
	bool isShow = false;
	std::atomic_bool threadStop = ATOMIC_VAR_INIT(false);
	
	// ---background---
	sf::RectangleShape background;
	void animateBackground();
	// ---background---
	
	// ---Game over text---
	const std::string gameOverText = "GAME OVER";
	std::unique_ptr<LabelController> gameOverLabel;
	void animateText();
	// ---Game over text---

	// ---Press any key text---
	const std::string pressAnyKeyText = "Press R or F5 if you want to try again";
	std::unique_ptr<LabelController> pressAnyKeyLabel;
	// ---Press any key text---
};
