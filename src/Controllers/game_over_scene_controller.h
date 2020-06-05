#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <thread>

#include "label_controller.h"


class GameOverSceneController
{
public:
	GameOverSceneController(const sf::Font &font);

	void draw(sf::RenderWindow &window);
	void setShowState(bool state);

private:
	bool isShow = false;
	// ---background---
	sf::RectangleShape background;
	std::thread backgroundThread;
	void animateBackground();
	// ---background---
	
	// ---text---
	const std::string finalText = "GAME OVER";
	std::unique_ptr<LabelController> gameOverLabel;
	std::string labelText = "";
	void animateText();
	// ---text---

	bool isVisible = false;
};
