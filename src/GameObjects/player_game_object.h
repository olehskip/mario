#pragma once
#include "../config.h"
#include "block_game_object.h"
#include "../Controllers/animation_controller.h"
#include <list>


class PlayerGameObject: public GameObject
{
public:
	PlayerGameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture);
	void move(Direction directionToMove, float deltaTime);
	// using GameObject::move;

	bool jump(float deltaTime);
	
	/*
	 * This function changes isStaying
	 * If the player is not RUN
	 * even if he is jumping(but not RUN left or right)
	 */
	void stay(float deltaTime);
	
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

	void headTouchedBlock();
	void die();
	bool isAlive() const;

private:
	/*
	 * This variable changes by PlayerGameObject::stay(...)
	 * If the player is not RUN
	 * even if he is jumping(but not RUN left or right)
	 */	
	bool isStaying = true;

	/*
	 * If the player is standing after jump, then he can jump again
	 */
	bool isAllowToJump = true;

	/*
	 * The direction can change on the ground
	 */
	Direction direction = Direction::RIGHT;

	/*
	 * The player can die only when:
	 * - he fell too low;
	 * - he encountered with an enemy
	 */
	bool mIsAlive = true;

	// ---animations---
	std::shared_ptr<AnimationController> runAnimation;
	std::shared_ptr<AnimationController> jumpAnimation;
	std::shared_ptr<AnimationController> dieAnimation;
	std::shared_ptr<AnimationController> currentAnimation;
	// ---animations---
};
typedef std::unique_ptr<PlayerGameObject> PlayerObject_ptr;
