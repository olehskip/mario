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
	float getSpeed() const { return player->getOffset().x; }

	void restart();
	void update();
	void draw(sf::RenderWindow &window); 
	void stay() { player->stay(deltaTime); } // temponary?? not finished

	// player functions
	void playerMoveLeft();
	void playerMoveRight();
	void playerJump();

	sf::Vector2f cameraController(const sf::Vector2f &cameraCenter);

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
};
