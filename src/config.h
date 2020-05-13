#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace config
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 800;
	const float WINDOW_SCALE = 1.3f;
	const int DYING_Y = 200;

	const sf::Vector2i VISIBLE_CELLS_COUNT = sf::Vector2i(120, 120);
	const int CELL_SIZE = 32;

	// const std::string MAIN_FONT_PATH = "data/fonts/pixeboy.ttf";
	const std::string MAIN_FONT_PATH = "data/fonts/digital-7.ttf";

	const sf::Color BACKGROUND_COLOR = sf::Color(104,136,249);

	// ---animations---
	
	// ---run animation---
	const float RUN_ANIMATION_SPEED = 4.6f;
	const unsigned int START_RUNNING_FRAME = 4, STOP_RUNNING_FRAME = 20;

	// ---jump animation---
	const float JUMP_ANIMATION_SPEED = 3.f;
	const unsigned int JUMPING_FRAME = 3, START_FALLING_FRAME = 4;

	// ---animations---
}
