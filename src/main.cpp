#include <SFML/Graphics.hpp>
#include <iostream>
#include "gamelogic.h"
#include "backgroundcontroller.h"

// g++ main.cpp gamelogic.cpp raincontroller.cpp textures.cpp GameObjects/animationcontroller.cpp GameObjects/gameobject.cpp GameObjects/playergameobject.cpp GameObjects/blockgameobject.cpp -o ./output -lsfml-graphics -lsfml-window -lsfml-system

int main()
{
	GameLogic gameLogic = GameLogic();
	sf::RenderWindow window(sf::VideoMode(config::WINDOW_WIDTH, config::WINDOW_HEIGHT), config::WINDOW_NAME);
	sf::View view(sf::Vector2f((config::WINDOW_WIDTH / 2) * config::WINDOW_SCALE, (config::WINDOW_HEIGHT / 2) * config::WINDOW_SCALE ),
				  sf::Vector2f(config::WINDOW_WIDTH, config::WINDOW_HEIGHT));
	view.zoom(config::WINDOW_SCALE);
	window.setView(view);
	window.setFramerateLimit(60);

	BackgroundController backgroundController;

	std::vector<sf::Text> labels; // all labels: time, score, etc
	labels.push_back(sf::Text()); // time
	sf::Font labelsFont;
	if(!labelsFont.loadFromFile(config::MAIN_FONT_PATH))
		return EXIT_FAILURE;
	for(auto &label: labels) {
		label.setFont(labelsFont);
		label.setCharacterSize(40);
		label.setFillColor(sf::Color::White);
		label.setPosition(5, 5);
	}
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		gameLogic.updateTime();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			gameLogic.playerMoveLeft();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			gameLogic.playerMoveRight();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			gameLogic.playerJump();

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			gameLogic.stay();

		window.clear(config::BACKGROUND_COLOR);

		gameLogic.update();
		labels[0].setString(std::to_string(gameLogic.getStopwatchTime()));

		const auto cameraPosition = gameLogic.cameraController(view.getCenter());
		view.move(cameraPosition);
		
		window.setView(view);
		backgroundController.move(cameraPosition);
		backgroundController.draw(window);
		for(auto &label: labels)
			label.move(cameraPosition);
		gameLogic.draw(window);

		
		window.draw(labels[0]);

		window.display();
	}

	window.close();
	return EXIT_SUCCESS;
}
