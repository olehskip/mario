#pragma once
#include "../config.h"
#include "block_game_object.h"
#include "../Controllers/animation_controller.h"
#include <list>

enum class PlayerYState
{
	JUMP,
	FALL,
	STAND
};

class PlayerGameObject: public GameObject
{
public:
	PlayerGameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture);
	void move(Direction directionToMove, float deltaTime);

	/*
	 * This function uses for finnally draw the sprite
	 */
	void move(sf::Vector2f offset);

	void jump(float deltaTime);
	
	/*
	 * This function changes isStaying
	 * If the player is not running
	 * even if he is jumping(but not running left or right)
	 */
	void stay(float deltaTime);

	void setOffset(sf::Vector2f newOffset);
	
	/*
	 * Updating the offset of the player
	 * Adding to the offset the gravity and the deceleration
	 * Checking if the offset is less for the max speed
	 */ 
	void updateMovement(float deltaTime) override;

	/*
	 * This function decides, which animation should draw
	 * and control the animation direction of mario
	 */
	void drawWithAnimation(sf::RenderWindow &window, float deltaTime);

	/*
	 * This function changes std::list<BlockObject_ptr> stayingOnBlocks
	 * Calls by GameLogic::checkForCollision()
	 */
	void setStayingOnBlocks(std::list<BlockObject_ptr> stayingOnBlocks);

	/*
	 * Stacked means the player is stacked of the left side of screen
	 * Need for not to let the player leave the game scene
	 */
	bool isStacked = false;

	/*
	 * Is player is jumping
	 * We need this variable for checking is player jumping right now
	 * for preventing endless jump
	 */
	bool isJumpingNow = false;

private:
	/*
	 * The list of blocks, which the player staying on
	 * The variable changes by PlayerGameObject::setStayingOnBlocks(...),
	 * which calles by GameLogic::checkForCollision(...)
	 */
	std::list<BlockObject_ptr> stayingOnBlocks;

	/*
	 * This variable changes by PlayerGameObject::stay(...)
	 * If the player is not running
	 * even if he is jumping(but not running left or right)
	 */	
	bool isStaying = true;

	/*
	 * If the player is standing after jump, then he can jump again
	 */
	bool isAlowedToJump = true;

	/*
	 * If the player jumped
	 * We need this variable for checking is player falling or jumping
	 */
	bool isJumped = false;

	/*
	 * This variable changes by PlayerGameObject::setStayingOnBlocks(...), 
	 * which calls in GameLogic::checkForCollision()
	 * If isOnGround == true, then the player is running or standing on a block
	 */	
	bool isOnGround = false;

	/*
	 * if the player is standing or running on ice
	 * that variable determines after 
	 */
	bool isOnIce = false;

	float getMaxXSpeed();
	/* 
	 * if the player jump we need to remember an acceleration BEFORE jump
	 */
	float maxXSpeedBeforeJump = config::player::JUMPING_MAX_SPEED;

	/*
	 * The direction can change on the ground
	 */
	Direction direction = Direction::RIGHT;

	/*
	 * if the player is falling to low then isAlive = true;
	 * TO DO
	 */
	void die();
	bool isAlive = false;

	// ---animations---
	std::shared_ptr<AnimationController> currentAnimation;
	std::shared_ptr<AnimationController> runAnimation;
	std::shared_ptr<AnimationController> jumpAnimation;
	// ---animations---
};
typedef std::shared_ptr<PlayerGameObject> PlayerObject_ptr;
