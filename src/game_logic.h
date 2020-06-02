#pragma once
#include "config.h"
#include "GameObjects/player_game_object.h"
#include "GameObjects/block_game_object.h"
#include "Loaders/textures_loader.h"
#include "Loaders/fonts_loader.h"
#include "Controllers/background_controller.h"
#include "Controllers/animated_label_controller.h"
#include "Controllers/audio_controller.h"

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
	float getSpeed() { return player->getOffset().x;}

	void keysManager();
	void playerJump();
	void playerNotJump();
	void toggleMute();

	FontsLoader fontsLoader;
	TexturesLoader texturesLoader;

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

private:
	void checkForCollision();
	std::vector<BlockObject_ptr> blocks;
	std::vector<BlockObject_ptr> scenery;
	PlayerObject_ptr player;
	sf::Clock clock, stopwatch;
	float deltaTime = 0.f;

	std::unique_ptr<BackgroundController> backgroundController;

	// at the start there is an animated label with developers contacts
	std::unique_ptr<AnimatedLabelController> titleAnimatedLabel;

	AudioController audioController;
};
