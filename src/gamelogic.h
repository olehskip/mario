#pragma once
#include "GameObjects/playergameobject.h"
#include "GameObjects/blockgameobject.h"
#include "config.h"
#include "textures.h"
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
	void stay(){player->stay(deltaTime);} // temponary?? not finished

	// player functions
	void playerMoveLeft();
	void playerMoveRight();
	void playerJump();
	float getPlayerXCenter();

	sf::Vector2f cameraController(const sf::Vector2f &cameraCenter);

	size_t getRandomNumber(size_t min, size_t max) {
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
	Textures textures;
	sf::Clock clock, stopwatch;
	float deltaTime = 0.f;
};
