#pragma once
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

private:
	std::unique_ptr<AnimationController> animation;
	Direction direction;
};
typedef std::unique_ptr<BotGameObject> BotObject_ptr;