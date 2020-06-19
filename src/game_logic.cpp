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
#include <iostream>
void GameLogic::restart()
{
	view.setCenter(config::window::WINDOW_WIDTH / 2 * config::window::WINDOW_ZOOM, 
		config::window::WINDOW_HEIGHT / 2 * config::window::WINDOW_ZOOM);

	player = std::make_unique<PlayerGameObject>(sf::Vector2f(3 * 64, 15 * 64), sf::Vector2f(1, 1), texturesLoader.getObject(TexturesID::MARIO_PLAYER_SPRITE));
	backgroundController = std::make_unique<BackgroundController>(texturesLoader.getObject(TexturesID::MOUNTAINS_BACKGROUND),
		texturesLoader.getObject(TexturesID::FOREST_BACKGROUND), texturesLoader.getObject(TexturesID::FIELD_BACKGROUND));

	// spawn for testing
	blocks.clear();

	for(size_t x = 3; x < 20; ++x) {
		blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * x, 14 * 64), sf::Vector2f(1, 1), 
			texturesLoader.getObject(TexturesID::LUCKY_BOX), true, BlockType::LUCKY_BOX, 2));
	}
	blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * 2, 13 * 64), sf::Vector2f(1, 1), 
		texturesLoader.getObject(TexturesID::LUCKY_BOX), true, BlockType::LUCKY_BOX));
	blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * 20, 13 * 64), sf::Vector2f(1, 1), 
		texturesLoader.getObject(TexturesID::LUCKY_BOX), true, BlockType::LUCKY_BOX));

	for(int x = -5; x < 1000; ++x) {
		blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * x, 19 * 64), sf::Vector2f(1, 1), 
			texturesLoader.getObject(TexturesID::GRASS_BRICK), true));
	}
	for(size_t y = 20; y < 23; ++y) {
		for(size_t x = 0; x < 1000; ++x) {
			blocks.push_back(std::make_unique<BlockGameObject>(sf::Vector2f(64 * x, y * 64), sf::Vector2f(1, 1), 
				texturesLoader.getObject(TexturesID::BOTTOM_BRICK), true));
		}
	}

	enemies.clear();
	enemies.push_back(std::make_unique<BotGameObject>(sf::Vector2f(6 * 64, 64 * 10), sf::Vector2f(1, 1), 
		texturesLoader.getObject(TexturesID::GOMBA_SPRITE), Direction::RIGHT));
	enemies.push_back(std::make_unique<BotGameObject>(sf::Vector2f(10 * 64, 64 * 10), sf::Vector2f(1, 1), 
		texturesLoader.getObject(TexturesID::GOMBA_SPRITE), Direction::LEFT));
	for(size_t x = 10; x < 16; ++x) {
		enemies.push_back(std::make_unique<BotGameObject>(sf::Vector2f(x * 100, 64 * 15), sf::Vector2f(1, 1), 
			texturesLoader.getObject(TexturesID::GOMBA_SPRITE), Direction::RIGHT));
	}

	coins.clear();
	for(size_t x = 10; x < 15; ++x) {
		for(size_t y = 16; y < 19; ++y)
			addCoin(sf::Vector2f(x * 64, y * 64), CoinState::STAND);
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
	fontsLoader.getObject(FontsID::PIXEBOY), 35 * config::window::WINDOW_ZOOM, sf::Color::White, std::string("0000"));
	coinsLabels.second->centerOriginX();
	labels.push_back(coinsLabels.first);
	labels.push_back(coinsLabels.second);

	audioController.startPlayingMusic();

	gameOverSceneController = std::make_unique<GameOverSceneController>(fontsLoader.getObject(FontsID::_8_BIT_ARCADE));
	pauseController = std::make_unique<PauseController>(fontsLoader.getObject(FontsID::_8_BIT_ARCADE));

	FPSLabel = std::make_unique<LabelController>(sf::Vector2f(0, 0), fontsLoader.getObject(FontsID::PIXEBOY),
		35 * config::window::WINDOW_ZOOM, sf::Color::White, std::string("0000000000000000"));
	FPSLabel->setPosition(sf::Vector2f(0, config::window::WINDOW_HEIGHT * config::window::WINDOW_ZOOM - 
		FPSLabel->getGlobalBounds().height * 2 - 5));
	score = Score();
	coinsCount = 0;
	timer.restart();
	timerValue = 999.f;
	clock.restart();
}
#include <iostream>
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
			if(blocks[nearestTouchedBlockIndex]->getCoin()) {
				const auto blockRect = blocks[nearestTouchedBlockIndex]->getGlobalBounds();
				addCoin(sf::Vector2f(blockRect.left + blockRect.width / 2.f, blockRect.top), CoinState::JUMP);
			}
		}
		verticalCollisionWithBlocks(*player);
		if(player->isStandingOnAnyBlock)
			score.resetStreak();
	}
	player->finalMove();
	for(auto &enemy: enemies) {
		enemy->updateMovement(deltaTime);
		horizontalCollisionController(*enemy);
		if(verticalCollisionWithBlocks(*enemy) && enemy->getOffset().y == 0)
			enemy->changeDirection();
		enemy->finalMove();
	}

	if(enemies.size() > 1) {
		for(size_t i = 1; i < enemies.size(); ++i) {
			if(!enemies[0]->isAlive()) break;
			if(!enemies[i]->isAlive() || (enemies[0]->isChangedDirection() && enemies[i]->isChangedDirection())) continue;
			if(verticalCollisionController(*enemies[0], *enemies[i], IsChangeOffset::FIRST_AND_SECOND)) {
				enemies[0]->changeDirection();
				enemies[i]->changeDirection();
			}
		}

		for(size_t i = 1; i < size_t(enemies.size() / 2); ++i) {
			if(!enemies[i]->isAlive()) continue;
			for(size_t j = size_t(enemies.size() / 2); j < enemies.size(); ++j) {
				if(!enemies[j]->isAlive() || (enemies[i]->isChangedDirection() && enemies[j]->isChangedDirection())) continue;
				if(verticalCollisionController(*enemies[i], *enemies[j], IsChangeOffset::FIRST_AND_SECOND)) {
					enemies[i]->changeDirection();
					enemies[j]->changeDirection();
				}
			}
		}
	}

	for(auto &coin: coins) {
		coin->updateMovement(deltaTime);
		horizontalCollisionController(*coin);
		coin->finalMove();
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
		coinsLabels.second->setText(convertNumberToStringWithNulls(coinsCount, 4));
	}
	
	audioMuteLable->update();
	fps.update();
	FPSLabel->setText(std::to_string(fps.getFPS()));
	// std::cout << fps.getFPS() << std::endl;
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
	for(auto &coin: coins) {
		if(isDrawObject(coin->getGlobalBounds()))
			coin->animate(deltaTime);
		coin->draw(window);
	}

	titleAnimatedLabel->draw(window);
	audioMuteLable->draw(window);
	
	for(auto &pointsLabel: pointsLabels)
		pointsLabel->draw(window);

	gameOverSceneController->draw(window);
	pauseController->draw(window);
	for(auto &label: labels)
		label->draw(window);

	FPSLabel->draw(window, fps.getColor());
	
	const auto cameraPosition = cameraController();
	view.move(cameraPosition);
	scrollBackground(cameraPosition);
}

bool GameLogic::isDrawObject(sf::FloatRect globalBounds)
{
	return globalBounds.left > view.getCenter().x - config::window::WINDOW_WIDTH / 2 * config::window::WINDOW_ZOOM ||
		globalBounds.left + globalBounds.width < view.getCenter().x + config::window::WINDOW_WIDTH / 2 * config::window::WINDOW_ZOOM;
}

void GameLogic::keysManager(bool isFocused)
{
	if(pauseController->isPaused()) return;
	if(player->isAlive() && isFocused) {
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
	FPSLabel->move(offset);
}

template<typename T>
std::vector<size_t> GameLogic::horizontalCollisionController(T &gameObject)
{
	std::vector<size_t> output;
	const auto globalBounds = gameObject.getGlobalBounds();

	gameObject.isStandingOnAnyBlock = false;
	// check for horizontal collision
	for(auto &block: blocks) {
		if(!block->hasCollision) continue;
		const auto blockRect = block->getGlobalBounds();
		if(globalBounds.left < blockRect.left + blockRect.width && globalBounds.left + globalBounds.width > blockRect.left) { // x
			// if the the gameObject head touched a block
			if(gameObject.getOffset().y < 0 && globalBounds.top + gameObject.getOffset().y > blockRect.top  && 
			   globalBounds.top + gameObject.getOffset().y <= blockRect.top + blockRect.height) {
				if constexpr (!std::is_same_v<T, CoinGameObject>) {
					gameObject.setOffset(sf::Vector2f(gameObject.getOffset().x, blockRect.height + blockRect.top - globalBounds.top));
					output.push_back(std::distance(blocks.begin(), std::find(blocks.begin(), blocks.end(), block)));
				}
			}

			/*
			 * if the gameObject is stacked to put in the right place
			 * or
			 * if the gameObject is staying on the right edge of a block do not touch him
			 */
			else if(globalBounds.top + gameObject.getOffset().y < blockRect.top && 
			   globalBounds.top + globalBounds.height + gameObject.getOffset().y > blockRect.top) {
				
				gameObject.isStandingOnAnyBlock = true;
				if constexpr (std::is_same_v<T, BotGameObject>) {
					if(block->isStartedJumping()) {
						gameObject.setOffset(sf::Vector2f(0, -10));
						onKillEnemy(gameObject);
					}
				}
				if constexpr (std::is_same_v<T, CoinGameObject>) {
					/* 
					 * if a coin falls and reached the ground, then the player earned it,
					 * but if the coin stays on the ground - the player need take it
					 * OR
					 * if the coin stays on block, and that block was touched by the player head
					 */
					if((gameObject.coinState == CoinState::JUMP && gameObject.getOffset().y > 0))
						onCatchCoin(gameObject);
				}
				else
					gameObject.setOffset(sf::Vector2f(gameObject.getOffset().x, blockRect.top - (globalBounds.top + globalBounds.height)));
			}
		}
	}

	return output;
}

template<typename T1, typename T2>
bool GameLogic::verticalCollisionController(T1 &firstGameObject, T2 &secondGameObject, IsChangeOffset isChangeOffset)
{
	if(!firstGameObject.hasCollision || !secondGameObject.hasCollision) return false;
	const auto firstGlobalBounds = firstGameObject.getGlobalBounds();
	const auto secondGlobalBounds = secondGameObject.getGlobalBounds();
	bool isCollision = false;
	
	// check for vertical collision

	if(firstGlobalBounds.top + firstGameObject.getOffset().y < secondGlobalBounds.top + secondGlobalBounds.height && 
		firstGlobalBounds.top + firstGlobalBounds.height + firstGameObject.getOffset().y > secondGlobalBounds.top) {
		// from the left to the right
		if(firstGlobalBounds.left + firstGlobalBounds.width + firstGameObject.getOffset().x > secondGlobalBounds.left && 
		    firstGlobalBounds.left + firstGlobalBounds.width + firstGameObject.getOffset().x < secondGlobalBounds.left + secondGlobalBounds.width) {
				if(isChangeOffset == IsChangeOffset::FIRST)
					firstGameObject.setOffset(sf::Vector2f(secondGlobalBounds.left - firstGlobalBounds.left - firstGlobalBounds.width, 
						firstGameObject.getOffset().y));
				else if(isChangeOffset == IsChangeOffset::FIRST_AND_SECOND) {
					const auto tempOffset = secondGlobalBounds.left - firstGlobalBounds.left - firstGlobalBounds.width;
					firstGameObject.setOffset(sf::Vector2f(tempOffset / 2, 
						firstGameObject.getOffset().y));
					secondGameObject.setOffset(sf::Vector2f(-tempOffset / 2, 
						secondGameObject.getOffset().y));	
				}
				isCollision = true;
		}
		// from the right to the left
		else if(firstGlobalBounds.left + firstGameObject.getOffset().x < secondGlobalBounds.left + secondGlobalBounds.width && 
		    firstGlobalBounds.left + firstGlobalBounds.width + firstGameObject.getOffset().x > secondGlobalBounds.left + secondGlobalBounds.width) {
				if(isChangeOffset == IsChangeOffset::FIRST)
					firstGameObject.setOffset(sf::Vector2f(secondGlobalBounds.left + secondGlobalBounds.width - firstGlobalBounds.left, 
						firstGameObject.getOffset().y));
				else if(isChangeOffset == IsChangeOffset::FIRST_AND_SECOND) {
					const auto tempOffset = secondGlobalBounds.left + secondGlobalBounds.width - firstGlobalBounds.left;
					firstGameObject.setOffset(sf::Vector2f(tempOffset / 2, 
						firstGameObject.getOffset().y));
					secondGameObject.setOffset(sf::Vector2f(-tempOffset / 2, 
						secondGameObject.getOffset().y));
				}
				
				isCollision = true;
		}
	}

	return isCollision;
}

template<typename T1>
bool GameLogic::verticalCollisionWithBlocks(T1 &gameObject)
{
	bool output = false;
	for(auto &block: blocks) {
		if(verticalCollisionController(gameObject, *block, IsChangeOffset::FIRST))
			output = true;
	}
	return output;
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

	for(auto it = coins.rbegin(); it != coins.rend(); ++it) {
		if((it->get()->getPosition().y > config::DIE_OXIS_Y || verticalCollisionController(*player, *it->get())) && !it->get()->isAlreadyEarned())
			onCatchCoin(*it->get());
		if(it->get()->isNeedToRemove())
			coins.erase(std::remove(coins.begin(), coins.end(), *it));
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
			else if(verticalCollisionController(*player, *enemy))
				gameOver();
		}
	}
}

void GameLogic::onKillEnemy(BotGameObject &botGameObject)
{
	if(!botGameObject.isAlive()) return;
	player->setOffset(sf::Vector2f(player->getOffset().x, -10));
	addPointLabel(sf::Vector2f(botGameObject.getGlobalBounds().left, botGameObject.getGlobalBounds().top), score.increaseValue());
	audioController.playSound(SoundsID::MARIO_STOMPS);
	botGameObject.die();
}

void GameLogic::onCatchCoin(CoinGameObject &coinGameObject)
{
	if(coinGameObject.isAlreadyEarned() || coinGameObject.isNeedToRemove()) return;
	coinsCount++;
	coinGameObject.earn();
	coinGameObject.needToRemove();
	addPointLabel(sf::Vector2f(coinGameObject.getGlobalBounds().left + coinGameObject.getGlobalBounds().width / 2.f, 
		coinGameObject.getGlobalBounds().top), config::coin::COST);
	score.addValue(config::coin::COST);
	audioController.playSound(SoundsID::COIN);
}

void GameLogic::addPointLabel(sf::Vector2f pos, unsigned int value)
{
	pointsLabels.push_back(std::make_unique<PointsLabelController>(pos, fontsLoader.getObject(FontsID::PIXEBOY), 
		30 * config::window::WINDOW_ZOOM, sf::Color::White, value, 1));
}

void GameLogic::addCoin(sf::Vector2f pos, CoinState coinState)
{
	coins.push_back(std::make_unique<CoinGameObject>(pos, sf::Vector2f(1.3, 1.3), texturesLoader.getObject(TexturesID::COIN_SPRITE), coinState));
	if(coinState == CoinState::JUMP)
		coins.back()->jumpUp(deltaTime);
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

void GameLogic::Score::addValue(unsigned int value)
{
	scoreValue += value;
}
