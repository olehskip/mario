#pragma once
#include "../config.h"
#include "game_object.h"
#include "../Controllers/animation_controller.h"


enum class CoinState
{
	STAND,
	JUMP,
};

class CoinGameObject: public GameObject
{
public:
	CoinGameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture, CoinState _coinState);
	void updateMovement(float deltaTime) override;
	void animate(float deltaTime) override;
	const CoinState coinState;

	bool isAlreadyEarned() const;
	void earn();

	void jumpUp(float deltaTime);

private:
	std::unique_ptr<AnimationController> animation;
	bool mIsAreladyEarned = false;
	sf::Vector2f globalOffset;
	bool isJumping = false;
};
