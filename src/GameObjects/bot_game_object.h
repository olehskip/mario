#pragma once
#include <SFML/System/Clock.hpp>
#include <functional>

#include "game_object.h"
#include "../Controllers/animation_controller.h"
#include "../config.h"

class BotGameObject: public GameObject
{
public:
	BotGameObject(sf::Vector2f pos, sf::Vector2f scale, sf::Texture &texture, Direction spawnDirection);

	void updateMovement(float deltaTime) override;
	void drawWithAnimation(sf::RenderWindow &window, float deltaTime);

	void changeDirection();

	bool isAlive() const;
	void die();

private:
	bool mIsAlive = true;
	sf::Clock dieStopwatch;
	std::shared_ptr<AnimationController> currentAnimation;
	std::shared_ptr<AnimationController> runAnimation;
	std::shared_ptr<AnimationController> dieAnimation;
	Direction direction;
};
typedef std::unique_ptr<BotGameObject> BotObject_ptr;

// class GoombaBot
// {

// };

