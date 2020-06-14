#pragma once
#include "temponary_label_controller.h"

#include <string>
#include <memory>


/* 
 * The difference between PointsLabelController and TemponaryLabelController: the second endless and repeats, 
 * when the first uses only for one time use and deletes after
 */

class PointsLabelController: private LabelController
{
public:
	PointsLabelController(sf::Vector2f pos, const sf::Font &font, unsigned int fontSize, sf::Color color, unsigned int scoreValue, float _visibleTime);

	void update(float deltaTime);
	void draw(sf::RenderWindow &window) override;
	bool isEnded() const;

	// this function uses, when the player runs and the camera is scrolls
	void moveX(float x);
	const float visibleTime;

private:
	sf::Clock stopwatch;
};
typedef std::unique_ptr<PointsLabelController> PointsLabel_ptr;
