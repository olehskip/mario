#include "pause_controller.h"

PauseController::PauseController(const sf::Font &font)
{
	labelController = std::make_unique<LabelController>(sf::Vector2f(0, 0), font, config::PAUSE_FONT_SIZE * config::window::WINDOW_ZOOM, 
		sf::Color::White, "Pause");
	labelController->centerOrigin();
	labelController->toCenterX(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM);
	labelController->toCenterY(config::window::WINDOW_HEIGHT * config::window::WINDOW_ZOOM);
	labelController->blink(true, 0.5f);
}

void PauseController::togglePause(float windowLeft)
{
	mIsPaused = !mIsPaused;
	if(mIsPaused) {
		labelController->toCenterX(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM);
		labelController->move(sf::Vector2f(windowLeft, 0));
	}
}

void PauseController::unpause()
{
	mIsPaused = false;
}

bool PauseController::isPaused() const
{
	return mIsPaused;
}

void PauseController::draw(sf::RenderWindow &window)
{
	if(mIsPaused)
		labelController->draw(window);
}
