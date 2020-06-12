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
#include "Controllers/points_label_controller.h"
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
	// if a game object over the game scene don't draw it
	bool isDrawObject(sf::FloatRect globalBounds);

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
	std::vector<PointsLabelController> pointsLabels;

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
	sf::Vector2f cameraController();
	std::unique_ptr<BackgroundController> backgroundController;
	void scrollBackground(sf::Vector2f offset);
	sf::View view;
	// ---camera---

	class Score {
		public:
			unsigned int getScoreValue() const;
			/*
			 * This function calculates the score according to streak
			 * Points streak is enable when:
			 * the player jumps on multiple enemies without touching the ground
			 * or kicks a shell to clear a line of foes
			 * 
			 * The system is:
			 * 1) 100 - 2) 200 - 3) 400 - 4) 500 - 5) 800 - 6) 1000 - 7) 2000 - 8) 4000 - 9) 5000 - 10) 8000 - 11) 1UP - ... - N) 1UP
			 */
			void resetStreak();
			unsigned int increaseValue();

		private:
			unsigned int scoreValue = 0;
			unsigned int streak = 0;
	} score;
};
