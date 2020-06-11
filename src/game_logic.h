#pragma once
#include "config.h"
#include "GameObjects/player_game_object.h"
#include "GameObjects/block_game_object.h"
#include "GameObjects/bot_game_object.h"
#include "Loaders/textures_loader.h"
#include "Loaders/fonts_loader.h"
#include "Controllers/background_controller.h"
#include "Controllers/animated_label_controller.h"
#include "Controllers/temponary_label_controller.h"
#include "Controllers/audio_controller.h"
#include "Controllers/game_over_scene_controller.h"

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

	void keysManager();
	void keysManager(sf::Keyboard::Key key);

	FontsLoader fontsLoader;
	TexturesLoader texturesLoader;

	const sf::View &getView() const;

private:
	std::vector<size_t> horizontalCollisionController(GameObject &gameObject);
	bool verticalCollisionController(GameObject &gameObject);
	bool isBlockCanJump = true;

	void gameOver();
	void killer();

	std::vector<BlockObject_ptr> blocks;
	// std::vector<BlockObject_ptr> scenery;
	std::vector<BotObject_ptr> enemies;
	PlayerObject_ptr player;
	sf::Clock clock, stopwatch;
	float deltaTime = 0.f;

	// at the start there is an animated label with developers contacts
	std::unique_ptr<AnimatedLabelController> titleAnimatedLabel;
	std::unique_ptr<TemponaryLabelController> audioMuteLable;
	std::vector<LabelController> labels; // all labels: time, score, etc

	AudioController audioController;

	std::unique_ptr<GameOverSceneController> gameOverSceneController;

	// ---camera---
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
	std::unique_ptr<BackgroundController> backgroundController;
	void scrollBackground(sf::Vector2f offset);
	sf::View view;
	// ---camera---
};
