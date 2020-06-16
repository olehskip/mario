#pragma once
#include "../config.h"
#include "label_controller.h"


class PauseController
{
public:
	PauseController(const sf::Font &font);

	void togglePause(float windowLeft);
	void unpause();
	bool isPaused() const;

	void draw(sf::RenderWindow &window);

private:
	bool mIsPaused = false;
	Label_ptr labelController;
};
