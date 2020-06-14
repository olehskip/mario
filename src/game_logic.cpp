#include "game_logic.h"

GameLogic::GameLogic()
{
	view.setSize(config::window::WINDOW_WIDTH, config::window::WINDOW_HEIGHT);
	view.zoom(config::window::WINDOW_ZOOM);

	restart();
	titleAnimatedLabel = std::make_unique<AnimatedLabelController>(sf::Vector2f(20, 650), fontsLoader.getObject(FontsID::PIXEBOY), 
		30 * config::window::WINDOW_ZOOM, sf::Color::White, config::window::TITLE_TEXT, 15);
	titleAnimatedLabel->toCenterY(config::window::WINDOW_HEIGHT * config::window::WINDOW_ZOOM);

	audioMuteLable = std::make_unique<TemponaryLabelController>(sf::Vector2f(0, 0), fontsLoader.getObject(FontsID::PIXEBOY), 
		30 * config::window::WINDOW_ZOOM, sf::Color::White, "Audio is muted", 2.f);
	audioMuteLable->toTopY();
	audioMuteLable->toCenterX(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM);
	audioMuteLable->setText("");
}

void GameLogic::updateTime()
{
	deltaTime = clock.getElapsedTime().asSeconds();
	clock.restart();
}

float GameLogic::getDeltaTime() const
{
	return clock.getElapsedTime().asSeconds();
}

int GameLogic::getStopwatchTime() const
{
	return int(stopwatch.getElapsedTime().asSeconds());
}

void GameLogic::restart()
{
	view.setCenter(config::window::WINDOW_WIDTH / 2 * config::window::WINDOW_ZOOM, 
		config::window::WINDOW_HEIGHT / 2 * config::window::WINDOW_ZOOM);

	player = std::make_unique<PlayerGameObject>(sf::Vector2f(3 * 64, 15 * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::MARIO_PLAYER_SPRITE));
	backgroundController = std::make_unique<BackgroundController>(texturesLoader.getObject(TexturesID::MOUNTAINS_BACKGROUND),
		texturesLoader.getObject(TexturesID::FOREST_BACKGROUND), texturesLoader.getObject(TexturesID::FIELD_BACKGROUND));

	// spawn for testing
	blocks.clear();

	for(int x = 3; x < 20; ++x) {
		blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * x, 14 * 64), sf::Vector2f(1, 1), 
			texturesLoader.getObject(TexturesID::LUCKY_BOX), true, BlockType::LUCKY_BOX));
	}
	blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * 2, 13 * 64), sf::Vector2f(1, 1), 
		texturesLoader.getObject(TexturesID::LUCKY_BOX), true, BlockType::LUCKY_BOX));
	blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * 20, 13 * 64), sf::Vector2f(1, 1), 
		texturesLoader.getObject(TexturesID::LUCKY_BOX), true, BlockType::LUCKY_BOX));

	for(int x = -5; x < 1000; ++x) {
		blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * x, 19 * 64), sf::Vector2f(1, 1), 
			texturesLoader.getObject(TexturesID::GRASS_BRICK), true));
	}
	for(int y = 20; y < 23; ++y) {
		for(int x = 0; x < 1000; ++x) {
			blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * x, y * 64), sf::Vector2f(1, 1), 
				texturesLoader.getObject(TexturesID::BOTTOM_BRICK), true));
		}
	}

	enemies.clear();
	enemies.push_back(std::make_unique<BotGameObject>(sf::Vector2f(6 * 64, 64 * 10), sf::Vector2f(1, 1), 
		texturesLoader.getObject(TexturesID::GOMBA_SPRITE), Direction::RIGHT));
	for(int x = 10; x < 15; ++x) {
		enemies.push_back(std::make_unique<BotGameObject>(sf::Vector2f(x * 100, 64 * 15), sf::Vector2f(1, 1), 
			texturesLoader.getObject(TexturesID::GOMBA_SPRITE), Direction::RIGHT));
	}

	pointsLabels.clear();
	labels.clear();
	labels.push_back(LabelController(sf::Vector2f(10, 0), fontsLoader.getObject(FontsID::PIXEBOY), 30 * config::window::WINDOW_ZOOM, 
	sf::Color::White, std::string())); // time

	audioController.startPlayingMusic();

	gameOverSceneController = std::make_unique<GameOverSceneController>(fontsLoader.getObject(FontsID::_8_BIT_ARCADE));

	score = Score();
	stopwatch.restart();
	clock.restart();
}

void GameLogic::update()
{
	player->updateMovement(deltaTime);
	for(auto &block: blocks)
		block->updateMovement(deltaTime);

	if(player->isAlive()) {
		const auto touchedBlocks = horizontalCollisionController(*player);
		if(touchedBlocks.size() > 0 && isBlockCanJump) {
			const size_t nearestTouchedBlockIndex = [](std::vector<size_t> indexes, std::vector<BlockObject_ptr> &_blocks, sf::FloatRect playerGlobalBounds)
			{
				std::pair<float, size_t> nearestBlock = std::make_pair(std::numeric_limits<float>::max(), -1);
				for(size_t index: indexes) {
					float currentDistance = std::abs((playerGlobalBounds.left + playerGlobalBounds.width) / 2 - 
						(_blocks[index]->getGlobalBounds().left + _blocks[index]->getGlobalBounds().width) / 2);
					if(currentDistance < nearestBlock.first)
						nearestBlock = std::make_pair(currentDistance, index);
				}
				return nearestBlock.second;
			}(touchedBlocks, blocks, player->getGlobalBounds());
			blocks[nearestTouchedBlockIndex]->jumpUp(deltaTime);
			player->headTouchedBlock();
			isBlockCanJump = false;
		}
		verticalCollisionController(*player);
		if(player->isStandingOnAnyBlock)
			score.resetStreak();
	}
	for(auto &enemy: enemies) {
		enemy->updateMovement(deltaTime);
		horizontalCollisionController(*enemy);
		if(verticalCollisionController(*enemy) && enemy->getOffset().y == 0)
			enemy->changeDirection();
	}
	killer();
	audioController.update();
	if(player->isAlive()) {
		for(auto itt = pointsLabels.rbegin(); itt != pointsLabels.rend(); ++itt) {
			itt->get()->update(deltaTime);
			if(itt->get()->isEnded())
				pointsLabels.erase(std::remove(pointsLabels.begin(), pointsLabels.end(), *itt));
		}
		labels[0].setText(std::to_string(getStopwatchTime()));
	}
	
	audioMuteLable->update();
}

void GameLogic::draw(sf::RenderWindow &window)
{
	backgroundController->draw(window);
	for(auto &block: blocks) {
		if(isDrawObject(block->getGlobalBounds()))
			block->draw(window);
	}
	// for(auto &decor: scenery)
	// 	decor->draw(window);
	player->drawWithAnimation(window, deltaTime);
	for(auto &enemy: enemies) {
		if(isDrawObject(enemy->getGlobalBounds()))
			enemy->drawWithAnimation(window, deltaTime);
	}
	titleAnimatedLabel->draw(window);
	audioMuteLable->draw(window);
	
	for(auto &pointsLabel: pointsLabels)
		pointsLabel->draw(window);

	gameOverSceneController->draw(window);
	for(auto &label: labels)
		label.draw(window);
	
	const auto cameraPosition = cameraController();
	view.move(cameraPosition);
	scrollBackground(cameraPosition);
}

bool GameLogic::isDrawObject(sf::FloatRect globalBounds)
{
	return globalBounds.left > view.getCenter().x - config::window::WINDOW_WIDTH / 2 * config::window::WINDOW_ZOOM ||
		globalBounds.left + globalBounds.width < view.getCenter().x + config::window::WINDOW_WIDTH / 2 * config::window::WINDOW_ZOOM;
}

void GameLogic::keysManager()
{
	if(player->isAlive()) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			player->move(Direction::LEFT, deltaTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			player->move(Direction::RIGHT, deltaTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if(player->jump(deltaTime)) {
				isBlockCanJump = true;
				audioController.playSound(SoundsID::MARIO_JUMPS);
			}
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
			audioMuteLable->show("Audio is muted");
		else
			audioMuteLable->show("Audio is unmuted");
	}
	else if(key == sf::Keyboard::R || key == sf::Keyboard::F5)
		restart();
}

const sf::View &GameLogic::getView() const
{
	return view;
}

sf::Vector2f GameLogic::cameraController()
{
	const auto windowLeft = view.getCenter().x - config::window::WINDOW_WIDTH / 2 * config::window::WINDOW_ZOOM;
	
	if(player->getSpriteCopy().getGlobalBounds().left <= windowLeft) {
		player->setOffset(sf::Vector2f(-(player->getSpriteCopy().getGlobalBounds().left - windowLeft), player->getOffset().y));
		player->isStacked = true;
	}
	else 
		player->isStacked = false;

	if(player->getOffset().x > 0 && player->getPosition().x >= view.getCenter().x)
		return sf::Vector2f(player->getOffset().x, 0);
	else
		return sf::Vector2f(0, 0);
}

void GameLogic::scrollBackground(sf::Vector2f offset)
{
	backgroundController->move(offset);
	audioMuteLable->move(offset);
	for(auto &pointsLabel: pointsLabels)
		pointsLabel->moveX(offset.x);
	for(auto &label: labels)
		label.move(offset);
}

std::vector<size_t> GameLogic::horizontalCollisionController(GameObject &gameObject)
{
	std::vector<size_t> output;
	const auto globalBounds = gameObject.getGlobalBounds();

	gameObject.isStandingOnAnyBlock = false;
	// check for horizontal collision
	for(auto &block: blocks) {
		if(!block->isHasCollision) continue;
		const auto blockRect = block->getGlobalBounds();
		if(globalBounds.left < blockRect.left + blockRect.width && globalBounds.left + globalBounds.width > blockRect.left) { // x
			// if the the gameObject head touched a block
			if(gameObject.getOffset().y < 0 && globalBounds.top + gameObject.getOffset().y > blockRect.top  && 
			   globalBounds.top + gameObject.getOffset().y <= blockRect.top + blockRect.height) {
				gameObject.setOffset(sf::Vector2f(gameObject.getOffset().x, blockRect.height + blockRect.top - globalBounds.top));
				output.push_back(std::distance(blocks.begin(), std::find(blocks.begin(), blocks.end(), block)));
			}

			// if the gameObject is stacked to put in the right place
			// or
			// if the gameObject is staying on the right edge of a block do not touch him
			else if(globalBounds.top + gameObject.getOffset().y < blockRect.top && 
			   globalBounds.top + globalBounds.height + gameObject.getOffset().y > blockRect.top) {
				gameObject.setOffset(sf::Vector2f(gameObject.getOffset().x, blockRect.top - (globalBounds.top + globalBounds.height)));
				gameObject.isStandingOnAnyBlock = true;
			}
		}
	}

	return output;
}

bool GameLogic::verticalCollisionController(GameObject &gameObject)
{
	const auto globalBounds = gameObject.getGlobalBounds();
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
			}
			// from the right to the left
			else if(gameObject.getOffset().x < 0 && globalBounds.left + gameObject.getOffset().x < blockRect.left + blockRect.width && 
				    globalBounds.left + globalBounds.width + gameObject.getOffset().x > blockRect.left + blockRect.width) {
				gameObject.setOffset(sf::Vector2f(blockRect.left + blockRect.width - globalBounds.left, gameObject.getOffset().y));
				isCollision = true;
			}
		}
	}

	return isCollision;
}

void GameLogic::gameOver()
{
	gameOverSceneController->show(view.getCenter().x - (config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM) / 2);
	player->die();
	audioController.stopPlayingMusic();
	audioController.playSound(SoundsID::MARIO_DIES);
	for(auto &label: labels)
		label.blink(true, 0.4f);
}

void GameLogic::killer()
{
	/* The enemies killer, then can die only when:
	 * they fell tow low,
	 * the player jumped on them
	 * 
	 * The player killer, he can die only when:
	 * he fell to low
	 * he encountered with an enemy
	 */

	// an enemy fell too low
	for(auto it = enemies.rbegin(); it != enemies.rend(); ++it) {
		if(it->get()->getPosition().y > config::DIE_OXIS_Y || it->get()->isNeedToRemove())
			enemies.erase(std::remove(enemies.begin(), enemies.end(), *it));
	}

	// the player fell too low
	if(player->isAlive() && player->getPosition().y > config::DIE_OXIS_Y)
		gameOver();

	if(player->isAlive()) {
		const auto globalBounds = player->getGlobalBounds();
		for(auto &enemy: enemies) {
			if(!enemy->isAlive()) continue;
			const auto enemyRect = enemy->getGlobalBounds();
			if((player->getOffset().y > 0 && globalBounds.top + player->getOffset().y < enemyRect.top && 
			   globalBounds.top + globalBounds.height + player->getOffset().y  > enemyRect.top - enemyRect.height / 2) &&
				((globalBounds.left + globalBounds.width + player->getOffset().x > enemyRect.left && 
				globalBounds.left + globalBounds.width + player->getOffset().x < enemyRect.left + enemyRect.width) ||
				(globalBounds.left + player->getOffset().x < enemyRect.left + enemyRect.width && 
				globalBounds.left + globalBounds.width + player->getOffset().x > enemyRect.left + enemyRect.width))) {
					player->setOffset(sf::Vector2f(player->getOffset().x, -10));
					pointsLabels.push_back(std::make_unique<PointsLabelController>(sf::Vector2f(enemy->getGlobalBounds().left, enemy->getGlobalBounds().top),
						fontsLoader.getObject(FontsID::PIXEBOY), 30 * config::window::WINDOW_ZOOM, sf::Color::White, 
						score.increaseValue(), 1));
					enemy->die();
				}
			// the player encountered with an enemy
			else if((globalBounds.top + player->getOffset().y < enemyRect.top + enemyRect.height && 
				globalBounds.top + globalBounds.height + player->getOffset().y > enemyRect.top) &&
				((globalBounds.left + globalBounds.width + player->getOffset().x > enemyRect.left && 
				globalBounds.left + globalBounds.width + player->getOffset().x < enemyRect.left + enemyRect.width) ||
				(globalBounds.left + player->getOffset().x < enemyRect.left + enemyRect.width && 
				globalBounds.left + globalBounds.width + player->getOffset().x > enemyRect.left + enemyRect.width)))
					gameOver();
		}
	}
}

unsigned int GameLogic::Score::getScoreValue() const
{
	return scoreValue;
}

void GameLogic::Score::resetStreak()
{
	streak = 1;
}

unsigned int GameLogic::Score::increaseValue()
{
	/* 
	 * The system is:
	 * 1) 100 - 2) 200 - 3) 400 - 4) 500 - 5) 800 - 6) 1000 - 7) 2000 - 8) 4000 - 9) 5000 - 10) 8000 - 11) 1UP - ... - N) 1UP
	 */

	// sorry, I really hate switch
	unsigned int scoreIncrease = scoreValue;
	streak++;
	if(streak == 1)
		scoreIncrease = 100;
	else if(streak == 2)
		scoreIncrease = 200;
	else if(streak == 3)
		scoreIncrease = 400;
	else if(streak == 4)
		scoreIncrease = 500;
	else if(streak == 5)
		scoreIncrease = 800;
	else if(streak == 6)
		scoreIncrease = 1000;
	else if(streak == 7)
		scoreIncrease = 2000;
	else if(streak == 8)
		scoreIncrease = 4000;
	else if(streak == 9)
		scoreIncrease = 5000;
	else if(streak == 10)
		scoreIncrease = 8000;
	else if(streak > 10) {
		streak = 10;
		scoreIncrease = 8000;
	}
	scoreValue += scoreIncrease;
	return scoreIncrease;
}
