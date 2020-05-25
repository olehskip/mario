#pragma once
#include "../config.h"
#include "blockgameobject.h"
#include "animationcontroller.h"
#include <list>

enum class Direction
{
	LEFT,
	RIGHT
};

class PlayerGameObject: public GameObject
{
public:
	PlayerGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture);
	void move(Direction directionToMove, float deltaTime);
	void move(sf::Vector2f offset);
	void jump(float deltaTime);
	void stay(float deltaTime);
	void setOffset(sf::Vector2f newOffset);
	void updateMovement(float deltaTime) override;
	void drawAnimation(sf::RenderWindow &window, float deltaTime);

	void setStayingOnBlocks(std::list<BlockObject_ptr> stayingOnBlocks);
	bool isStacked = false; // stacked means stacked of the left side of screen (when the player is running back)
	bool getIsStaying() const;

private:
	std::list<BlockObject_ptr> stayingOnBlocks;
	bool isStaying = true;
	bool isAlowedToJump = true;
	bool isJumped = false;
	bool isOnGround = false;
	bool isOnIce = false;
	Direction direction = Direction::RIGHT;

	void die();
	bool isAlive = false;

	// animations
	std::shared_ptr<AnimationController> currentAnimation;
	std::shared_ptr<AnimationController> runAnimation;
	std::shared_ptr<AnimationController> jumpAnimation;
};
typedef std::shared_ptr<PlayerGameObject> PlayerObject_ptr;
