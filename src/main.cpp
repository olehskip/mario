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

	sf::View view(sf::Vector2f((config::window::WINDOW_WIDTH / 2) * config::window::WINDOW_ZOOM, (config::window::WINDOW_HEIGHT / 2) * config::window::WINDOW_ZOOM),
				  sf::Vector2f(config::window::WINDOW_WIDTH, config::window::WINDOW_HEIGHT));
	view.zoom(config::window::WINDOW_ZOOM);
	window.setView(view);
	
	std::vector<LabelController> labels; // all labels: time, score, etc
	labels.push_back(LabelController(gameLogic.fontsLoader.getObject(FontsID::DIGITAL7), 40 * config::window::WINDOW_ZOOM, sf::Color::White, std::string(), sf::Vector2f(10, 5))); // time

	bool isFocused = true;
	while(window.isOpen()) {
		sf::Event event;
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
		gameLogic.updateTime();

		if(isFocused)
			gameLogic.keysManager();

		window.clear(config::window::BACKGROUND_COLOR);

		gameLogic.update();
		gameLogic.draw(window);
		
		labels[0].setText(std::to_string(gameLogic.getStopwatchTime()));
		const auto cameraPosition = gameLogic.cameraController(view.getCenter());

		view.move(cameraPosition);
		
		window.setView(view);
		gameLogic.scrollBackground(cameraPosition);

		for(auto &label: labels) {
			label.move(cameraPosition);
			label.draw(window);
		}

		window.display();
	}

	window.close();
	return EXIT_SUCCESS;
}
