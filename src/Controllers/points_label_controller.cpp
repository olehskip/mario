#include "points_label_controller.h"

PointsLabelController::PointsLabelController(sf::Vector2f pos, const sf::Font &font, unsigned int fontSize, sf::Color color, unsigned int scoreValue, float _visibleTime):
	LabelController(pos, font, fontSize, color, std::to_string(scoreValue)), visibleTime(_visibleTime)
{
	centerOriginX();
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
	return stopwatch.getElapsedTime().asSeconds() >= visibleTime;
}

void PointsLabelController::moveX(float x)
{
	textObj.move(x, 0);
}
