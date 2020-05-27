#include "game_logic.h"

GameLogic::GameLogic()
{
	// change in the future
	srand(time(NULL));
	
	player = std::make_unique<PlayerGameObject>(sf::Vector2f(50, 17 * 64), sf::Vector2f(1, 1), texturesLoader.getTexture(TexturesID::MARIO_PLAYER));
	titleAnimatedLabel = std::make_unique<AnimatedLabelController>
						 (fontsLoader.getFont(FontsID::PIXEBOY), 30 * config::WINDOW_ZOOM, sf::Color::White, std::string(config::TITLE_TEXT), sf::Vector2f(20, 650), 15);
	// spawn for testing

	// for(int i = 0; i < 10; ++i) {
	// 	blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * 10, i * 64), sf::Vector2f(1, 1), texturesLoader.getTexture(TexturesID::BOTTOM_BRICK), true));
	// }

	for(int x = 0; x < 40; ++x) {
		if((rand() % 9) - 7 < 0) continue;
		float randomX = getRandomNumber(150 * x - 20, 150 * x + 20);
		int randomTexture = getRandomNumber(int(TexturesID::BUSH1), int(TexturesID::SMALL_TREE1));
		scenery.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(randomX, 19 * 64 - texturesLoader.getTexture(static_cast<TexturesID>(randomTexture))->getSize().y), sf::Vector2f(1, 1), texturesLoader.getTexture(static_cast<TexturesID>(randomTexture)), false));
	}
	
	for(int x = 0; x < 100; ++x) {
		blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * x, 19 * 64), sf::Vector2f(1, 1), texturesLoader.getTexture(TexturesID::GRASS_BRICK), true));
	}
	for(int y = 20; y < 23; ++y) {
		for(int x = 0; x < 100; ++x) {
			blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * x, y * 64), sf::Vector2f(1, 1), texturesLoader.getTexture(TexturesID::BOTTOM_BRICK), true));
		}
	}
	for(int y = 19; y < 23; ++y) {
		for(int x = 100; x < 200; ++x) {
			blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * x, y * 64), sf::Vector2f(1, 1), texturesLoader.getTexture(TexturesID::ICE_BLOCK), true, BlockType::ICE));
		}
	}
	// for(int i = 100; i < 150; ++i) {
	// 	blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * i, 20 * 64), sf::Vector2f(1, 1), texturesLoader.getTexture(TexturesID::SIMLE_BRICK), true));
	// }
	// for(int i = 150; i < 2000; ++i) {
	// 	blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * i, 20 * 64), sf::Vector2f(1, 1), texturesLoader.getTexture(TexturesID::SOLID_BRICK), true));
	// }
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

void GameLogic::update()
{
	player->updateMovement(deltaTime);
	checkForCollision();
	player->move(player->getOffset());
}

void GameLogic::draw(sf::RenderWindow &window)
{
	backgroundController.draw(window);
	player->drawAnimation(window, deltaTime);
	for(auto &block: blocks)
		block->draw(window);
	for(auto &decor: scenery)
		decor->draw(window);
	player->draw(window);
	titleAnimatedLabel->draw(window);
}

// player functions
void GameLogic::playerMoveLeft()
{
	player->move(Direction::LEFT, deltaTime);
}

void GameLogic::playerMoveRight()
{
	player->move(Direction::RIGHT, deltaTime);
}

void GameLogic::playerJump()
{
	player->jump(deltaTime);
}

sf::Vector2f GameLogic::cameraController(const sf::Vector2f &cameraCenter)
{
	const auto windowLeft = cameraCenter.x - config::WINDOW_WIDTH / 2 * config::WINDOW_ZOOM;
	if(player->getSpriteCopy().getGlobalBounds().left <= windowLeft) {
		player->setOffset(sf::Vector2f(-(player->getSpriteCopy().getGlobalBounds().left - windowLeft), player->getOffset().y));
		player->isStacked = true;
	}
	else 
		player->isStacked = false;

	if(bool(player->getOffset().x > 0) && bool(player->getPosition().x >= cameraCenter.x))
		return sf::Vector2f(player->getOffset().x, 0);
	else
		return sf::Vector2f(0, 0);
}

void GameLogic::scrollBackground(sf::Vector2f offset)
{
	backgroundController.move(offset);
}

void GameLogic::checkForCollision()
{
	const auto playerGlobalBounds = player->getGlobalBounds();
	const auto playerPosition = player->getPosition();

	std::list<BlockObject_ptr> touchedBlocks, stayingOnBlocks;
	// check for horizontal collision
	for(auto &block: blocks) {
		if(!block->isHasCollision) continue;
		const auto blockRect = block->getGlobalBounds();
		if(playerGlobalBounds.left < blockRect.left + blockRect.width && playerGlobalBounds.left + playerGlobalBounds.width> blockRect.left) { // x)
			// if the the player head is touched a block
			if(player->getOffset().y < 0 && playerGlobalBounds.top + player->getOffset().y >= blockRect.top  && playerGlobalBounds.top + player->getOffset().y < blockRect.top + blockRect.height) {
				player->setOffset(sf::Vector2f(player->getOffset().x, blockRect.height + blockRect.top - playerGlobalBounds.top));
				touchedBlocks.push_back(block);
				// block->jumpUp(deltaTime);
				break;
			}
			// if the player is stacked to put in the right place
			// or
			// if the player is staying on the right edge of a block do not touch him
			if(player->getOffset().y > 0 && playerGlobalBounds.top + player->getOffset().y < blockRect.top && playerGlobalBounds.top + playerGlobalBounds.height + player->getOffset().y  > blockRect.top) { // y
				player->setOffset(sf::Vector2f(player->getOffset().x, blockRect.top - (playerGlobalBounds.top + playerGlobalBounds.height)));
				stayingOnBlocks.push_back(block);
			}
		}
	}
	player->setStayingOnBlocks(stayingOnBlocks);


	// check for vertical collision
	for(auto &block: blocks) {
		if(!block->isHasCollision) continue;
		const auto blockRect = block->getGlobalBounds();
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