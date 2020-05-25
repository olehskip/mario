#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace config
{
	const std::string WINDOW_NAME = "mario remake CXC";
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 800;
	const float WINDOW_SCALE = 1.3f;
	const int DYING_Y = 200;

	const sf::Vector2i VISIBLE_CELLS_COUNT = sf::Vector2i(120, 120);
	const int CELL_SIZE = 32;

	// const std::string MAIN_FONT_PATH = "data/fonts/pixeboy.ttf";
	const std::string MAIN_FONT_PATH = "data/fonts/digital-7.ttf";

	const sf::Color BACKGROUND_COLOR = sf::Color(104, 136, 249);

	// ---animations---

		// ---run animation---
		const float RUN_ANIMATION_SPEED = 4.6f;
		const unsigned int RUN_ANIMATION_FRAMES_COUNT = 26, START_RUNNING_FRAME = 4, STOP_RUNNING_FRAME = 20;
		// ---run animation---

		// ---jump animation---
		const float JUMP_ANIMATION_SPEED = 3.f;
		const unsigned int JUMP_ANIMATION_FRAMES_COUNT = 4, JUMPING_FRAME = 3;
		// ---jump animation---

	// ---animations---

	// ---live objects constants---
		const float GRAVITY = 1.f;
		const float MAX_FALLING_SPEED = 22.f;

		// ---player constants---
			// ---jumping---
			const float PLAYER_JUMPING_ACCELERATION = 6.f;
			const float PLAYER_JUMPING_MAX_SPEED = 20.f; 
			// ---jumping---

			// ---running
			const float PLAYER_RUNNING_ACCELERATION = 0.3f;
			const float PLAYER_RUNNING_DECELERATION = 0.5f;
			const float PLAYER_RUNNING_MAX_SPEED = 10.f;

			const float PLAYER_RUNNIMG_ACCELERATION_ON_ICE= 0.23f;
			const float PLAYER_RUNNIMG_DECELARATION_ON_ICE = 0.35f;
			const float PLAYER_RUNNING_MAX_SPEED_ON_ICE = 13.f;
			// ---running

	// ---live objects constants---
	
	const bool IS_LOGGING_ENABLED = false;
}
