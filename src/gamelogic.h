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
	void update(sf::RenderWindow &window);
	void stay(){player->stay(deltaTime);} // temponary?? not finished

	// player functions
	void playerMoveLeft();
	void playerMoveRight();
	void playerJump();

	// [[deprecated]]
	sf::Vector2f getOffset(){return player->getOffset(); }; // temponary
	// [[deprecated]]
	sf::FloatRect getGlobalBounds(){return player->getSpriteCopy().getGlobalBounds();}
	// [[deprecated]]
	sf::Vector2f getPosition(){return player->getSpriteCopy().getPosition();}
size_t getRandomNumber(size_t min, size_t max) {
    static std::mt19937 rng;
    rng.seed(std::random_device()());
    //rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

private:
	void checkForCollision();
	void cameraController(sf::RenderWindow &window);
	void centerCameraOnY();

	std::vector<BlockObject_ptr> blocks;
	std::vector<BlockObject_ptr> scenery;
	PlayerObject_ptr player;
	Textures textures;
	sf::Clock clock, stopwatch;
	float deltaTime = 0.f;
};
