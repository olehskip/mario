#pragma once
#include "config.h"
#include "GameObjects/player_game_object.h"
#include "GameObjects/block_game_object.h"
#include "Loaders/textures_loader.h"
#include "Loaders/fonts_loader.h"
#include "Controllers/background_controller.h"
#include "Controllers/animated_label_controller.h"

#include <random>
#include "time.h"

class GameLogic
{
public:
	GameLogic();
	void updateTime();
	float getDeltaTime() const;
	int getStopwatchTime() const;

	void restart();
	void update();
	void draw(sf::RenderWindow &window); 
	void stay() { player->stay(deltaTime); } // temponary?? not finished

	// player functions
	void playerMoveLeft();
	void playerMoveRight();
	void playerJump();

	/*
	 * Contrlling camera moving
	 * 
	 * This function does not let mario leave from the game scene
	 * and controls that mario runs only at center or left part of the game scene
	 * 
	 * @param cameraCenter means the center of camera for not to let mario move only at center and left part of the scene
	 * @return the offset so that the camera moves by it
	 */
	sf::Vector2f cameraController(const sf::Vector2f &cameraCenter);

	void scrollBackground(sf::Vector2f offset);

	/*
	 * This function temponary, because there will be a map constructor
	 */
	int getRandomNumber(int min, int max) {
		static std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

		return dist(rng);
	}

private:
	void checkForCollision();
	std::vector<BlockObject_ptr> blocks;
	std::vector<BlockObject_ptr> scenery;
	PlayerObject_ptr player;
	sf::Clock clock, stopwatch;
	float deltaTime = 0.f;

	BackgroundController backgroundController;
	std::unique_ptr<AnimatedLabelController> titleAnimatedLabel;
};
