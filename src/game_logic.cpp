#include "game_logic.h"

GameLogic::GameLogic()
{
	// change in the future
	srand(time(NULL));
	
	player = std::make_unique<PlayerGameObject>(sf::Vector2f(50, 17 * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::MARIO_PLAYER_SPRITE));
	backgroundController = std::make_unique<BackgroundController>(texturesLoader.getObject(TexturesID::MOUNTAINS_BACKGROUND),
		texturesLoader.getObject(TexturesID::FOREST_BACKGROUND), texturesLoader.getObject(TexturesID::FIELD_BACKGROUND));
	titleAnimatedLabel = std::make_unique<AnimatedLabelController>(fontsLoader.getObject(FontsID::PIXEBOY), 
		30 * config::window::WINDOW_ZOOM, sf::Color::White, std::string(config::window::TITLE_TEXT), sf::Vector2f(20, 650), 15);
	
	// spawn for testing
	for(int x = 3; x < 6; ++x) {
		blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * x, 14 * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::LUCKY_BOX), true, BlockType::LUCKY_BOX));
	}

	for(int x = 0; x < 100; ++x) {
		blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * x, 19 * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::GRASS_BRICK), true));
	}
	for(int y = 20; y < 23; ++y) {
		for(int x = 0; x < 100; ++x) {
			blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * x, y * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::BOTTOM_BRICK), true));
		}
	}
	for(int y = 19; y < 23; ++y) {
		for(int x = 100; x < 200; ++x) {
			blocks.push_back(std::make_shared<BlockGameObject>(sf::Vector2f(64 * x, y * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::ICE_BLOCK), true, BlockType::ICE));
		}
	}

	audioIndicator.setTexture(texturesLoader.getObject(TexturesID::AUDIO_UNMUTED));
	audioIndicator.setPosition(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM - audioIndicator.getGlobalBounds().width * config::window::WINDOW_ZOOM, 5);
	audioIndicator.scale(1.3f, 1.3f);
	audioController.startPlayingMusic();
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
	for(auto &block: blocks)
		block->updateMovement(deltaTime);
	audioController.update();
}

void GameLogic::draw(sf::RenderWindow &window)
{
	backgroundController->draw(window);
	for(auto &block: blocks)
		block->draw(window);
	for(auto &decor: scenery)
		decor->draw(window);
	player->drawWithAnimation(window, deltaTime);
	titleAnimatedLabel->draw(window);
	window.draw(audioIndicator);
}

void GameLogic::keysManager()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player->move(Direction::LEFT, deltaTime);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player->move(Direction::RIGHT, deltaTime);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if(player->jump(deltaTime))
			audioController.playSound(SoundsID::MARIO_JUMPS);
	}
	else
		player->isJumpingNow = false;

	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player->stay(deltaTime);
}

void GameLogic::keysManager(sf::Keyboard::Key key)
{
	if(key == sf::Keyboard::M) {
		if(audioController.toggleMute())
			audioIndicator.setTexture(texturesLoader.getObject(TexturesID::AUDIO_MUTED));
		else
			audioIndicator.setTexture(texturesLoader.getObject(TexturesID::AUDIO_UNMUTED));
	}
}

sf::Vector2f GameLogic::cameraController(const sf::Vector2f &cameraCenter)
{
	const auto windowLeft = cameraCenter.x - config::window::WINDOW_WIDTH / 2 * config::window::WINDOW_ZOOM;
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
	backgroundController->move(offset);
	audioIndicator.move(offset);
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
			if(player->getOffset().y < 0 && playerGlobalBounds.top + player->getOffset().y > blockRect.top  && playerGlobalBounds.top + player->getOffset().y < blockRect.top + blockRect.height) {
				player->setOffset(sf::Vector2f(player->getOffset().x, blockRect.height + blockRect.top - playerGlobalBounds.top + 5));
				touchedBlocks.push_back(block);
				block->jumpUp(deltaTime);
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