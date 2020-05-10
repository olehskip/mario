#include <SFML/Graphics.hpp>
#include <iostream>
#include "gamelogic.h"

// g++ main.cpp gamelogic.cpp textures.cpp GameObjects/gameobject.cpp GameObjects/playergameobject.cpp GameObjects/blockgameobject.cpp -o ./output -lsfml-graphics -lsfml-window -lsfml-system

int main()
{
	std::cout << "started biatch" << std::endl;
	GameLogic gameLogic = GameLogic();
	sf::RenderWindow window(sf::VideoMode(config::WINDOW_WIDTH, config::WINDOW_HEIGHT), "test");
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window.getSize().x, window.getSize().y));
	view.zoom(1.3);
	
	window.setFramerateLimit(60);

	std::vector<sf::Text> labels; // all labels: time, score, etc
	labels.push_back(sf::Text()); // time

	sf::Font labelsFont;
	if(!labelsFont.loadFromFile(config::MAIN_FONT_PATH))
		return EXIT_FAILURE;
	for(auto &label: labels) {
		label.setFont(labelsFont);
		label.setCharacterSize(40);
		label.setFillColor(sf::Color::White);
		label.setPosition(25, 0);
	}
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			gameLogic.playerMoveLeft();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			gameLogic.playerMoveRight();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			gameLogic.playerJump();

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			gameLogic.stay();
		gameLogic.updateTime();

		window.clear(config::BACKGROUND_COLOR);

		gameLogic.update(window);
		view.setCenter(gameLogic.getCameraPosition());
		window.setView(view);

		labels[0].setString(std::to_string(gameLogic.getStopwatchTime()));
		labels[0].setPosition(0, 0);
		window.draw(labels[0]);

		window.display();
	}

	window.close();
	return EXIT_SUCCESS;
}
