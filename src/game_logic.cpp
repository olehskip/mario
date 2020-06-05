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
		blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * x, 14 * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::LUCKY_BOX), true, BlockType::LUCKY_BOX));
	}

	for(int x = -5; x < 1000; ++x) {
		blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * x, 19 * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::GRASS_BRICK), true));
	}
	for(int y = 20; y < 23; ++y) {
		for(int x = 0; x < 1000; ++x) {
			blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * x, y * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::BOTTOM_BRICK), true));
		}
	}
	blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * 3, 18 * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::SOLID_BRICK), true));
	blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * 10, 18 * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::SOLID_BRICK), true));

	enemies.push_back(std::make_unique<BotGameObject>(sf::Vector2f(250, 800), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::GOMBA_SPRITE), Direction::RIGHT));

	audioIndicator.setTexture(texturesLoader.getObject(TexturesID::AUDIO_UNMUTED));
	audioIndicator.setPosition(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM - audioIndicator.getGlobalBounds().width * config::window::WINDOW_ZOOM, 5);
	audioIndicator.scale(1.3f, 1.3f);
	audioController.startPlayingMusic();

	gameOverSceneController = std::make_unique<GameOverSceneController>(fontsLoader.getObject(FontsID::_8_BIT_ARCADE));

	labels.push_back(LabelController(fontsLoader.getObject(FontsID::DIGITAL7), 40 * config::window::WINDOW_ZOOM, sf::Color::White, std::string(), sf::Vector2f(10, 5))); // time
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
	if(!player->isDead()) {
		horizontalCollisionController(*player);
		verticalCollisionController(*player);
	}
	for(auto &block: blocks)
		block->updateMovement(deltaTime);
	for(auto &enemy: enemies) {
		enemy->updateMovement(deltaTime);
		horizontalCollisionController(*enemy);
		if(verticalCollisionController(*enemy))
			enemy->changeDirection();
	}
	audioController.update();
	fallingObjectKiller();
	playerKiller();
	if(!player->isDead())
		labels[0].setText(std::to_string(getStopwatchTime()));
}

void GameLogic::draw(sf::RenderWindow &window)
{
	backgroundController->draw(window);
	for(auto &block: blocks)
		block->draw(window);
	for(auto &decor: scenery)
		decor->draw(window);
	player->drawWithAnimation(window, deltaTime);
	for(auto &enemy: enemies) 
		enemy->drawWithAnimation(window, deltaTime);
	titleAnimatedLabel->draw(window);
	window.draw(audioIndicator);
	gameOverSceneController->draw(window);
	for(auto &label: labels)
		label.draw(window);
}

void GameLogic::keysManager()
{
	if(!player->isDead()) {
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
	else
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
	for(auto &label: labels)
		label.move(offset);
}

bool GameLogic::horizontalCollisionController(GameObject &gameObject)
{
	const auto globalBounds = gameObject.getGlobalBounds();
	const auto position = gameObject.getPosition();
	bool isCollision = false;

	gameObject.isStandingOnAnyBlock = false;
	// check for horizontal collision
	for(auto &block: blocks) {
		if(!block->isHasCollision) continue;
		const auto blockRect = block->getGlobalBounds();
		if(globalBounds.left < blockRect.left + blockRect.width && globalBounds.left + globalBounds.width> blockRect.left) { // x
			// if the the gameObject head is touched a block
			if(gameObject.getOffset().y < 0 && globalBounds.top + gameObject.getOffset().y > blockRect.top  && 
			   globalBounds.top + gameObject.getOffset().y < blockRect.top + blockRect.height) {
				gameObject.setOffset(sf::Vector2f(gameObject.getOffset().x, blockRect.height + blockRect.top - globalBounds.top + 2));
				isCollision = true;
				break;
			}

			// if the gameObject is stacked to put in the right place
			// or
			// if the gameObject is staying on the right edge of a block do not touch him
			if(gameObject.getOffset().y > 0 && globalBounds.top + gameObject.getOffset().y < blockRect.top && 
			   globalBounds.top + globalBounds.height + gameObject.getOffset().y  > blockRect.top) {
				gameObject.setOffset(sf::Vector2f(gameObject.getOffset().x, blockRect.top - (globalBounds.top + globalBounds.height)));
				gameObject.isStandingOnAnyBlock = true;
				isCollision = true;
			}
		}
	}

	return isCollision;
}

bool GameLogic::verticalCollisionController(GameObject &gameObject)
{
	const auto globalBounds = gameObject.getGlobalBounds();
	const auto position = gameObject.getPosition();
	bool isCollision = false;
	
	// check for vertical collision
	for(auto &block: blocks) {
		if(!block->isHasCollision) continue;
		const auto blockRect = block->getGlobalBounds();

		if(globalBounds.top + gameObject.getOffset().y < blockRect.top + blockRect.height && 
		   globalBounds.top + globalBounds.height + gameObject.getOffset().y > blockRect.top) {
			// from the left to the right
			if(gameObject.getOffset().x > 0 && globalBounds.left + globalBounds.width + gameObject.getOffset().x > blockRect.left && 
			   globalBounds.left + globalBounds.width + gameObject.getOffset().x < blockRect.left + blockRect.width) {
				gameObject.setOffset(sf::Vector2f(blockRect.left - globalBounds.left - globalBounds.width, gameObject.getOffset().y));
				isCollision = true;
				break;
			}
			/// from the right to the left
			else if(gameObject.getOffset().x < 0 && globalBounds.left + gameObject.getOffset().x < blockRect.left + blockRect.width && 
				    globalBounds.left + globalBounds.width + gameObject.getOffset().x > blockRect.left + blockRect.width) {
				gameObject.setOffset(sf::Vector2f(blockRect.left + blockRect.width - globalBounds.left, gameObject.getOffset().y));
				isCollision = true;
				break;
			}
		}
	}

	return isCollision;
}

void GameLogic::fallingObjectKiller()
{
	for(auto it = enemies.rbegin(); it != enemies.rend(); ++it) {
			if(it->get()->getPosition().y > config::DIE_OXIS_Y)
				enemies.erase(std::remove(enemies.begin(), enemies.end(), *it));
	}
}

void GameLogic::playerKiller()
{
	if(player->isDead()) return;
    const auto globalBounds = player->getGlobalBounds();
	for(auto &enemy: enemies) {
		const auto enemyRect = enemy->getGlobalBounds();

		if(globalBounds.top + player->getOffset().y < enemyRect.top + enemyRect.height && 
		   globalBounds.top + globalBounds.height + player->getOffset().y > enemyRect.top) {
			
			if((globalBounds.left + globalBounds.width + player->getOffset().x > enemyRect.left && 
			   globalBounds.left + globalBounds.width + player->getOffset().x < enemyRect.left + enemyRect.width) ||
			   (globalBounds.left + player->getOffset().x < enemyRect.left + enemyRect.width && 
			   globalBounds.left + globalBounds.width + player->getOffset().x > enemyRect.left + enemyRect.width)) {
					gameOverSceneController->setShowState(true);
					player->die();
					audioController.stopPlayingMusic();
					audioController.playSound(SoundsID::MARIO_DIES);
					for(auto &label: labels)
						label.blink(true);
			  }

		}	
	}
}
