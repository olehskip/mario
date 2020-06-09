#include "game_over_scene_controller.h"

#include "../config.h"

GameOverSceneController::GameOverSceneController(const sf::Font &font)
{
	background.setFillColor(sf::Color(0, 0, 0, 0));
	background.setSize(sf::Vector2f(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM, config::window::WINDOW_HEIGHT * config::window::WINDOW_ZOOM));

	gameOverLabel = std::make_unique<LabelController>(font, 100 * config::window::WINDOW_ZOOM, sf::Color::White, gameOverText, sf::Vector2f(0, 0));
	gameOverLabel->toCenterX(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM);
	gameOverLabel->toCenterY(config::window::WINDOW_HEIGHT * config::window::WINDOW_ZOOM);
	gameOverLabel->setText("");

	pressAnyKeyLabel = std::make_unique<LabelController>(font, 30 * config::window::WINDOW_ZOOM, sf::Color::White, pressAnyKeyText, sf::Vector2f(0, 0));
	pressAnyKeyLabel->toBottomY(config::window::WINDOW_HEIGHT * config::window::WINDOW_ZOOM);
	pressAnyKeyLabel->toCenterX(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM);
	pressAnyKeyLabel->setText("");
}	

GameOverSceneController::~GameOverSceneController()
{
	threadStop = true;
}

void GameOverSceneController::draw(sf::RenderWindow &window)
{
	if(mIsShow) {
		window.draw(background);
		gameOverLabel->draw(window);
		pressAnyKeyLabel->draw(window);
	}
}

void GameOverSceneController::show(float cameraLeft)
{
	if(!mIsShow) {
		mIsShow = true;
		background.move(cameraLeft, 0);
		gameOverLabel->move(sf::Vector2f(cameraLeft, 0));
		pressAnyKeyLabel->move(sf::Vector2f(cameraLeft, 0));
		std::thread(&GameOverSceneController::animateBackground, this).detach();
	}
}

bool GameOverSceneController::isShow() const
{
	return mIsShow;
}

void GameOverSceneController::animateBackground()
{
	for(int i = 0; i < 256; ++i) {
		if(threadStop == true)
			return;
		{
			std::unique_lock<std::mutex> lock(mtx);
			background.setFillColor(sf::Color(0, 0, 0, i));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(3));
	}
	animateText();
}

void GameOverSceneController::animateText()
{
	for(auto oneChar: gameOverText) {
		if(threadStop == true)
			return;
		{
			std::unique_lock<std::mutex> lock(mtx);
			gameOverLabel->setText(gameOverLabel->getText() + oneChar);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
	pressAnyKeyLabel->setText(pressAnyKeyText);
}
