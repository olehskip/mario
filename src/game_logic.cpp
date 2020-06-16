#include "game_logic.h"

GameLogic::GameLogic()
{
	view.setSize(config::window::WINDOW_WIDTH, config::window::WINDOW_HEIGHT);
	view.zoom(config::window::WINDOW_ZOOM);

	titleAnimatedLabel = std::make_unique<AnimatedLabelController>(sf::Vector2f(20, 650), fontsLoader.getObject(FontsID::PIXEBOY), 
		30 * config::window::WINDOW_ZOOM, sf::Color::White, config::window::TITLE_TEXT, 15);
	titleAnimatedLabel->toCenterY(config::window::WINDOW_HEIGHT * config::window::WINDOW_ZOOM);

	audioMuteLable = std::make_unique<TemponaryLabelController>(sf::Vector2f(0, 0), fontsLoader.getObject(FontsID::PIXEBOY), 
		30 * config::window::WINDOW_ZOOM, sf::Color::White, "Audio is muted", 2.f);
	audioMuteLable->centerOrigin();
	audioMuteLable->toCenterX(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM);
	audioMuteLable->toCenterY(config::window::WINDOW_HEIGHT * config::window::WINDOW_ZOOM);
	audioMuteLable->setText("");

	restart();
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
	enemies.push_back(std::make_unique<BotGameObject>(sf::Vector2f(8 * 64, 64 * 15), sf::Vector2f(1, 1), 
		texturesLoader.getObject(TexturesID::GOMBA_SPRITE), Direction::LEFT));
	for(int x = 10; x < 15; ++x) {
		enemies.push_back(std::make_unique<BotGameObject>(sf::Vector2f(x * 100, 64 * 15), sf::Vector2f(1, 1), 
			texturesLoader.getObject(TexturesID::GOMBA_SPRITE), Direction::RIGHT));
	}

	pointsLabels.clear();
	labels.clear();
	timeLabels.first = std::make_shared<LabelController>(sf::Vector2f(20, 0), fontsLoader.getObject(FontsID::PIXEBOY), 
		35 * config::window::WINDOW_ZOOM, sf::Color::White, std::string("Time:"));
	timeLabels.second = std::make_shared<LabelController>(LabelController(sf::Vector2f(timeLabels.first->getGlobalBounds().left + 
		timeLabels.first->getGlobalBounds().width / 2.f, timeLabels.first->getGlobalBounds().top + timeLabels.first->getGlobalBounds().height),
		fontsLoader.getObject(FontsID::PIXEBOY), 35 * config::window::WINDOW_ZOOM,  sf::Color::White, std::string("100")));
	timeLabels.second->centerOriginX();
	labels.push_back(timeLabels.first);
	labels.push_back(timeLabels.second);
	
	livesLabels.first = std::make_shared<LabelController>(sf::Vector2f(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM / 3 + 10, 0), 
		fontsLoader.getObject(FontsID::PIXEBOY), 35 * config::window::WINDOW_ZOOM, sf::Color::White, std::string("Lives:"));
	livesLabels.second = std::make_shared<LabelController>(sf::Vector2f(livesLabels.first->getGlobalBounds().left, 
		timeLabels.second->getPosition().y), 
	fontsLoader.getObject(FontsID::PIXEBOY), 35 * config::window::WINDOW_ZOOM, sf::Color::White, std::string("0"));
	livesLabels.first->centerOriginX();
	livesLabels.second->centerOriginX();
	labels.push_back(livesLabels.first);
	labels.push_back(livesLabels.second);

	scoreLabels.first = std::make_shared<LabelController>(sf::Vector2f(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM * 2 / 3 - 10, 0), 
		fontsLoader.getObject(FontsID::PIXEBOY), 35 * config::window::WINDOW_ZOOM, sf::Color::White, std::string("Score:"));
	scoreLabels.second = std::make_shared<LabelController>(sf::Vector2f(scoreLabels.first->getGlobalBounds().left, 
		timeLabels.second->getPosition().y), 
	fontsLoader.getObject(FontsID::PIXEBOY), 35 * config::window::WINDOW_ZOOM, sf::Color::White, std::string("000000"));
	scoreLabels.first->centerOriginX();
	scoreLabels.second->centerOriginX();
	labels.push_back(scoreLabels.first);
	labels.push_back(scoreLabels.second);

	coinsLabels.first = std::make_shared<LabelController>(sf::Vector2f(0, 0), fontsLoader.getObject(FontsID::PIXEBOY), 
		35 * config::window::WINDOW_ZOOM, sf::Color::White, std::string("Coins:"));
	coinsLabels.first->setPosition(sf::Vector2f(config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM - 
		coinsLabels.first->getGlobalBounds().width - 20, 0));
	coinsLabels.second = std::make_shared<LabelController>(sf::Vector2f(coinsLabels.first->getGlobalBounds().left + 
		coinsLabels.first->getGlobalBounds().width / 2.f, timeLabels.second->getPosition().y), 
	fontsLoader.getObject(FontsID::PIXEBOY), 35 * config::window::WINDOW_ZOOM, sf::Color::White, std::string("0"));
	coinsLabels.second->centerOriginX();
	labels.push_back(coinsLabels.first);
	labels.push_back(coinsLabels.second);

	audioController.startPlayingMusic();

	gameOverSceneController = std::make_unique<GameOverSceneController>(fontsLoader.getObject(FontsID::_8_BIT_ARCADE));
	pauseController = std::make_unique<PauseController>(fontsLoader.getObject(FontsID::_8_BIT_ARCADE));

	score = Score();
	timer.restart();
	timerValue = 999.f;
	clock.restart();
}

void GameLogic::update()
{
	if(pauseController->isPaused()) return;

	if(timer.getElapsedTime().asSeconds() >= 1.f) {
		timerValue -= timer.getElapsedTime().asSeconds();
		timer.restart();
	}
	if(timerValue <= 0.f)
		gameOver();

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
	player->finalMove();
	for(auto &enemy: enemies) {
		enemy->updateMovement(deltaTime);
		horizontalCollisionController(*enemy);
		if(verticalCollisionController(*enemy) && enemy->getOffset().y == 0)
			enemy->changeDirection();
		enemy->finalMove();
	}
	killer();
	audioController.update();
	if(player->isAlive()) {
		for(auto itt = pointsLabels.rbegin(); itt != pointsLabels.rend(); ++itt) {
			itt->get()->update(deltaTime);
			if(itt->get()->isEnded())
				pointsLabels.erase(std::remove(pointsLabels.begin(), pointsLabels.end(), *itt));
		}
		timeLabels.second->setText(std::to_string(int(std::round(std::abs(timerValue)))));
		livesLabels.second->setText(std::to_string(player->getLivesCount()));
		scoreLabels.second->setText(convertNumberToStringWithNulls(score.getScoreValue(), 6));
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
	if(!pauseController->isPaused())
		player->animate(deltaTime);
	player->draw(window);
	for(auto &enemy: enemies) {
		if(isDrawObject(enemy->getGlobalBounds())) {
			if(!pauseController->isPaused())
				enemy->animate(deltaTime);
			enemy->draw(window);
		}
	}
	titleAnimatedLabel->draw(window);
	audioMuteLable->draw(window);
	
	for(auto &pointsLabel: pointsLabels)
		pointsLabel->draw(window);

	gameOverSceneController->draw(window);
	pauseController->draw(window);
	for(auto &label: labels)
		label->draw(window);
	
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
	if(pauseController->isPaused()) return;
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
	else if((key == sf::Keyboard::P || key == sf::Keyboard::Enter) && player->isAlive())
		pauseController->togglePause(view.getCenter().x - (config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM) / 2);
	else if(key == sf::Keyboard::R || key == sf::Keyboard::F5)
		restart();
}

const sf::View &GameLogic::getView() const
{
	return view;
}


std::string GameLogic::convertNumberToStringWithNulls(int number, size_t nullsCount)
{
	std::string output = "";
	const std::string convertedNumber = std::to_string(std::abs(number));
	for(size_t i = 0; i < nullsCount - convertedNumber.size(); ++i)
		output += "0";

	return output + convertedNumber;
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
		label->move(offset);
}

template<typename T>
std::vector<size_t> GameLogic::horizontalCollisionController(T &gameObject)
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
				if constexpr (std::is_same_v<T, BotGameObject>) {
					if(block->isStartedJumping()) {
						gameObject.setOffset(sf::Vector2f(0, -5));
						onKillEnemy(gameObject);
					}
				}
			}
		}
	}

	return output;
}

template<typename T>
bool GameLogic::verticalCollisionController(T &gameObject)
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
	pauseController->unpause();
	gameOverSceneController->show(view.getCenter().x - (config::window::WINDOW_WIDTH * config::window::WINDOW_ZOOM) / 2);
	player->die();
	audioController.stopPlayingMusic();
	audioController.playSound(SoundsID::MARIO_DIES);
	for(auto &label: labels)
		label->blink(true, 0.5f);
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
			   globalBounds.top + globalBounds.height + player->getOffset().y  > enemyRect.top - enemyRect.height / 3) &&
				((globalBounds.left + globalBounds.width + player->getOffset().x > enemyRect.left && 
				globalBounds.left + globalBounds.width + player->getOffset().x < enemyRect.left + enemyRect.width) ||
				(globalBounds.left + player->getOffset().x < enemyRect.left + enemyRect.width && 
				globalBounds.left + globalBounds.width + player->getOffset().x > enemyRect.left + enemyRect.width)))
					onKillEnemy(*enemy);
	
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

void GameLogic::onKillEnemy(BotGameObject &botGameObject)
{
	if(!botGameObject.isAlive()) return;
	player->setOffset(sf::Vector2f(player->getOffset().x, -10));
	pointsLabels.push_back(std::make_unique<PointsLabelController>(sf::Vector2f(botGameObject.getGlobalBounds().left, 
		botGameObject.getGlobalBounds().top),fontsLoader.getObject(FontsID::PIXEBOY), 30 * config::window::WINDOW_ZOOM, 
		sf::Color::White, score.increaseValue(), 1));
	audioController.playSound(SoundsID::MARIO_STOMPS);
	botGameObject.die();
}

unsigned int GameLogic::Score::getScoreValue() const
{
	return scoreValue;
}

void GameLogic::Score::resetStreak()
{
	streak = 0;
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
