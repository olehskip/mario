#include <SFML/Graphics.hpp>
#include <iostream>
#include "gamelogic.h"

// g++ main.cpp gamelogic.cpp textures.cpp GameObjects/gameobject.cpp GameObjects/playergameobject.cpp GameObjects/blockgameobject.cpp -o ./output -lsfml-graphics -lsfml-window -lsfml-system -pthread
// x86_64-w64-mingw32-g++ main.cpp gamelogic.cpp textures.cpp GameObjects/gameobject.cpp GameObjects/playergameobject.cpp GameObjects/blockgameobject.cpp -I/home/skip/SFML/include -L/home/skip/SFML/lib --static
// x86_64-w64-mingw32-g++ main.cpp -I/home/skip/SFML/include -L/home/skip/SFML/lib --static


int main()
{
	std::cout << "started biatch" << std::endl;
	GameLogic gameLogic = GameLogic();
	sf::RenderWindow window(sf::VideoMode(config::WINDOW_WIDTH, config::WINDOW_HEIGHT), "test");
	window.setFramerateLimit(60);

	std::vector<sf::Text> labels; // all labels: time, score, etc
	labels.push_back(sf::Text()); // time
	labels.push_back(sf::Text()); // time
	labels.push_back(sf::Text()); // time

	sf::Font labelsFont;
	if(!labelsFont.loadFromFile(config::MAIN_FONT_PATH))
		return EXIT_FAILURE;
	for(auto &label: labels) {
		label.setFont(labelsFont);
		label.setCharacterSize(30);
		label.setFillColor(sf::Color::Green);
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

		// labels[0].setString(std::to_string(gameLogic.getStopwatchTime()));
		// window.draw(labels[0]);

		labels[1].setPosition(gameLogic.getGlobalBounds().left + 15, gameLogic.getGlobalBounds().top - 50);
		labels[1].setString(std::to_string(int(gameLogic.getOffset().x)) + " " + std::to_string(int(gameLogic.getOffset().y)));
		window.draw(labels[1]);

		labels[2].setPosition(gameLogic.getGlobalBounds().left - 15, gameLogic.getGlobalBounds().top + gameLogic.getGlobalBounds().height);
		labels[2].setString(std::to_string(int(gameLogic.getPosition().x)) + " " + std::to_string(int(gameLogic.getPosition().y)));
		window.draw(labels[2]);

		window.display();
	}

	window.close();
	return EXIT_SUCCESS;
}
