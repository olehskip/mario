#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace config
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 800;
	const int DYING_Y = 200;

	const sf::Vector2i VISIBLE_CELLS_COUNT = sf::Vector2i(120, 120);
	const int CELL_SIZE = 32;

	// const std::string MAIN_FONT_PATH = "data/fonts/pixeboy.ttf";
	const std::string MAIN_FONT_PATH = "data/fonts/digital-7.ttf";

	const sf::Color BACKGROUND_COLOR = sf::Color(104,136,249);
}
