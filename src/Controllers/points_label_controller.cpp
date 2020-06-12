#include "points_label_controller.h"

PointsLabelController::PointsLabelController(sf::Vector2f pos, const sf::Font &font, unsigned int fontSize, sf::Color color, unsigned int scoreValue, float visibleTime):
	LabelController(pos, font, fontSize, color, std::to_string(scoreValue))
{
}

void PointsLabelController::update(float deltaTime)
{
	textObj.move(0, -4 * deltaTime * 60);
}

void PointsLabelController::draw(sf::RenderWindow &window) // override
{
	LabelController::draw(window);
}

bool PointsLabelController::isEnded() const
{
	return stopwatch.getElapsedTime().asSeconds() >= 1;
}

void PointsLabelController::moveX(float x)
{
	textObj.move(x, 0);
}
