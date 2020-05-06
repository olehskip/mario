#include "gamelogic.h"

GameLogic::GameLogic()
{
	// change in the future
	srand(time(NULL));

	player = std::make_unique<PlayerGameObject>(sf::Vector2f(100, 4 * 64), sf::Vector2f(1, 2), textures.getTexture(TexturesID::MARIO_PLAYER), sf::Vector2f(0.8, 10), sf::Vector2f(0.5, 1), sf::Vector2f(10, 20), 4.8);
	// blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(400, 3 * 64), sf::Vector2f(1, 1), std::string("data/textures/brick_down.png")));
	// for(int i = 0; i < 100; ++i)
	// 	scenery.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * i * 10, 7 * 64), sf::Vector2f(1, 1), textures.getTexture(TexturesID::BUSH), false));
	
	// spawn for testing
	for(int i = 0; i < 100; ++i) {
		if((rand() % 5) - 4 < 0) continue;
		float randomX = getRandomNumber(150 * i - 20, 150 * i + 20);
		int randomY = (rand() % 50) + 150;
		scenery.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(randomX, randomY), sf::Vector2f(1, 1), textures.getTexture(TexturesID::CLOUD), false));
	}

	for(int i = 0; i < 50; ++i) {
		if((rand() % 5) - 1 < 0) continue;
		float randomX = getRandomNumber(150 * i - 20, 150 * i + 20);
		int randomTexture = getRandomNumber(int(TexturesID::BUSH), int(TexturesID::SMALL_TREE1));
		scenery.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(randomX, 6 * 64), sf::Vector2f(1, 1), textures.getTexture(static_cast<TexturesID>(randomTexture)), false));
	}

	for(int i = 0; i < 50; ++i) {
		if(i % 2 == 0) continue;
		blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(i * 64, 2 * 64), sf::Vector2f(1, 1), textures.getTexture(TexturesID::LUCKY_BOX), true));
	}

	for(int i = 0; i < 100; ++i) {
		blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * i, 7 * 64), sf::Vector2f(1, 1), textures.getTexture(TexturesID::BOTTOM_BRICK), true));
	}
	for(int i = 50; i < 100; ++i) {
		blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * i, 7 * 64), sf::Vector2f(1, 1), textures.getTexture(TexturesID::GRASS_BRICK), true));
	}
	for(int i = 100; i < 150; ++i) {
		blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * i, 7 * 64), sf::Vector2f(1, 1), textures.getTexture(TexturesID::SIMLE_BRICK), true));
	}
	for(int i = 150; i < 200; ++i) {
		blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * i, 7 * 64), sf::Vector2f(1, 1), textures.getTexture(TexturesID::SOLID_BRICK), true));
	}

	// for(int i = 0; i < 10; ++i)
	// 	blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * 8, i * 64), sf::Vector2f(1, 1), textures.getTexture(TexturesID::BOTTOM_BRICK), true));
}

void GameLogic::updateTime()
{
	deltaTime = clock.getElapsedTime().asSeconds();
	clock.restart();
}

float GameLogic::getDeltaTime() const
{
	return deltaTime;
}

int GameLogic::getStopwatchTime() const
{
	return int(stopwatch.getElapsedTime().asSeconds());
}

void GameLogic::restart()
{
}

void GameLogic::update(sf::RenderWindow &window)
{
	player->updateMovement(deltaTime);
	checkForCollision();
	cameraController(window);
	centerCameraOnY();
	player->drawAnimation(window, deltaTime);
	player->draw(window);
}

void GameLogic::checkForCollision()
{
	const auto playerGlobalBounds = player->getSpriteCopy().getGlobalBounds();
	const auto playerPosition = player->getSpriteCopy().getPosition();

	std::vector<BlockObject_ptr> touchedBlocks;
	// check for horizontal collision
	for(auto &block: blocks) {
		if(!block->isHasCollision) continue;
		const auto blockRect = block->getSpriteCopy().getGlobalBounds();
		if(playerGlobalBounds.left < blockRect.left + blockRect.width && playerGlobalBounds.left + playerGlobalBounds.width> blockRect.left) { // x)
			// if the the player head is touched a block
			if(player->getOffset().y < 0 && playerGlobalBounds.top + player->getOffset().y >= blockRect.top && playerGlobalBounds.top + player->getOffset().y < blockRect.top + blockRect.height) {
				player->setOffset(sf::Vector2f(player->getOffset().x, blockRect.height + blockRect.top - playerGlobalBounds.top));
				touchedBlocks.push_back(block);
				// block->jumpUp();
				break;
			}
			// if the player is stacked to put in the right place
			// or
			// if the player is staying on the right edge of a block do not touch him
			if(player->getOffset().y > 0 && playerGlobalBounds.top + player->getOffset().y < blockRect.top && playerGlobalBounds.top + playerGlobalBounds.height + player->getOffset().y > blockRect.top) { // y
				player->setOffset(sf::Vector2f(player->getOffset().x, blockRect.top - (playerGlobalBounds.top + playerGlobalBounds.height)));
				player->setOnGround(true);
				break;
			}
			else 
				player->setOnGround(false);
		}
	}
	
	for(auto &block: touchedBlocks) {

	}

	// check for vertical collision
	for(auto &block: blocks) {
		if(!block->isHasCollision) continue;
		const auto blockRect = block->getSpriteCopy().getGlobalBounds();
		if(player->getOffset().x == 0) break;

		if(playerGlobalBounds.top + player->getOffset().y < blockRect.top + blockRect.height && playerGlobalBounds.top + playerGlobalBounds.height + player->getOffset().y > blockRect.top) {
			// from the left to the right
			if(player->getOffset().x > 0 && playerGlobalBounds.left + playerGlobalBounds.width + player->getOffset().x > blockRect.left && playerGlobalBounds.left + playerGlobalBounds.width + player->getOffset().x < blockRect.left + blockRect.width) {
				player->setOffset(sf::Vector2f(blockRect.left - playerGlobalBounds.left - playerGlobalBounds.width, player->getOffset().y));
				break;
			}
			/// from the right to the left
			else if(player->getOffset().x < 0 && playerGlobalBounds.left + player->getOffset().x < blockRect.left + blockRect.width && playerGlobalBounds.left + playerGlobalBounds.width + player->getOffset().x > blockRect.left + blockRect.width) {
				player->setOffset(sf::Vector2f(blockRect.left + blockRect.width - playerGlobalBounds.left, player->getOffset().y));
				break;
			}
		}
	}
}

void GameLogic::cameraController(sf::RenderWindow &window)
{
	if(player->getOffset().x < 0 || player->getSpriteCopy().getGlobalBounds().left <= config::WINDOW_WIDTH / 2 - player->getSpriteCopy().getGlobalBounds().width / 2) {
		player->move(sf::Vector2f(player->getOffset().x, 0));
		if(player->getSpriteCopy().getGlobalBounds().left <= 0) {
			player->setOffset(sf::Vector2f(-player->getSpriteCopy().getPosition().x, player->getOffset().y));
			player->isStacked = true;
		}
		else 
			player->isStacked = false;
	} 
	else {
		for(auto &block: blocks)
			block->move(sf::Vector2f(-player->getOffset().x, 0));
		for(auto &decor: scenery)
			decor->move(sf::Vector2f(-player->getOffset().x, 0));
	}
	for(auto &block: blocks) {
		block->move(sf::Vector2f(0, -player->getOffset().y));
		block->updateMovement(deltaTime);
		block->draw(window);
	}
	for(auto &decor: scenery) {
		decor->move(sf::Vector2f(0, -player->getOffset().y));
		decor->updateMovement(deltaTime);
		decor->draw(window);
	}
}

void GameLogic::centerCameraOnY()
{
	int playerCenterY = (player->getSpriteCopy().getGlobalBounds().top + player->getSpriteCopy().getGlobalBounds().height) / 2;
	int screenCenterY = config::WINDOW_HEIGHT / 2;
	// player->setOffset(sf::Vector2f(player->getOffset().x, screenCenterY - playerCenterY));
}

// player functions
void GameLogic::playerMoveLeft()
{
	player->moveLeft(deltaTime);
}

void GameLogic::playerMoveRight()
{
	player->moveRight(deltaTime);
}

void GameLogic::playerJump()
{
	player->jump(deltaTime);
}
