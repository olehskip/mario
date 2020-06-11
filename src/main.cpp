#include <SFML/Graphics.hpp>
#include "game_logic.h"

// g++ main.cpp gamelogic.cpp raincontroller.cpp texturesLoader.cpp GameObjects/animationcontroller.cpp GameObjects/gameobject.cpp GameObjects/playergameobject.cpp GameObjects/blockgameobject.cpp -o ./output -lsfml-graphics -lsfml-window -lsfml-system

int main()
{
	GameLogic gameLogic = GameLogic();
	sf::RenderWindow window(sf::VideoMode(config::window::WINDOW_WIDTH, config::window::WINDOW_HEIGHT), config::window::WINDOW_NAME);
	sf::Image icon;
	if(icon.loadFromFile("data/icons/icon.png"))
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setFramerateLimit(60);

	bool isFocused = true;
	while(window.isOpen()) {
		sf::Event event;
		gameLogic.updateTime();
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed)
				gameLogic.keysManager(event.key.code);
			else if(event.type == sf::Event::GainedFocus)
				isFocused = true;
			else if(event.type == sf::Event::LostFocus)
				isFocused = false;
		}

		if(isFocused)
			gameLogic.keysManager();

		window.clear(config::window::BACKGROUND_COLOR);
		gameLogic.update();
		gameLogic.draw(window);
		window.setView(gameLogic.getView());
		window.display();
	}

	window.close();
	return EXIT_SUCCESS;
}
