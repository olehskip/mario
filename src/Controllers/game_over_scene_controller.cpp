#include "game_over_scene_controller.h"

#include "../config.h"

GameOverSceneController::GameOverSceneController(const sf::Font &font)
{
	background.setFillColor(sf::Color(0, 0, 0, 0));
	background.setSize(sf::Vector2f(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM, config::window::WINDOW_HEIGHT * config::window::WINDOW_ZOOM));

	gameOverLabel = std::make_unique<LabelController>(font, 100 * config::window::WINDOW_ZOOM, sf::Color::White, finalText, sf::Vector2f(200, 500));
	gameOverLabel->centerX(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM);
	gameOverLabel->centerY(config::window::WINDOW_HEIGHT * config::window::WINDOW_ZOOM);
	gameOverLabel->setText("");
}	

void GameOverSceneController::draw(sf::RenderWindow &window)
{
	if(isShow) {
		window.draw(background);
		gameOverLabel->draw(window);
	}
}

void GameOverSceneController::setShowState(bool state)
{
	isShow = state;
	if(isShow) {
		std::thread(&GameOverSceneController::animateBackground, this).detach();
	}
}

void GameOverSceneController::animateBackground()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	for(int i = 0; i < 256; ++i) {
		background.setFillColor(sf::Color(0, 0, 0, i));
		std::this_thread::sleep_for(std::chrono::milliseconds(3));
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	animateText();

}

void GameOverSceneController::animateText()
{
	for(auto oneChar: finalText) {
		gameOverLabel->setText(gameOverLabel->getText() + oneChar);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
}
