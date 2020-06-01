#include "background_controller.h"

// ---Background---
Background::Background(const sf::Texture &mountains, const sf::Texture &forest, const sf::Texture &field)
{
	for(int i = 0; i < 3; ++i) 
		backgroundParts.push_back(sf::Sprite());
	
	backgroundParts[0].setTexture(mountains);
	backgroundParts[1].setTexture(forest);
	backgroundParts[2].setTexture(field);
	float scale = (config::WINDOW_HEIGHT * config::WINDOW_ZOOM) / 1000;

	for(auto &part: backgroundParts)
		part.setScale(sf::Vector2f(scale, scale));

	backgroundParts[0].setPosition(sf::Vector2f(0, config::MOUNTAINS_BACKGROUND_OFFSET_Y * backgroundParts[0].getScale().y));
	backgroundParts[1].setPosition(sf::Vector2f(0, config::FOREST_BACKGROUND_OFFSET_Y * backgroundParts[1].getScale().y));
	backgroundParts[2].setPosition(sf::Vector2f(0, config::FIELD_BACKGROUND_OFFSET_Y * backgroundParts[2].getScale().y));
}

void Background::draw(sf::RenderWindow &window)
{
	for(auto &part: backgroundParts)
		window.draw(part);
}

void Background::setPositionX(float x)
{
	for(auto &part: backgroundParts)
		part.setPosition(sf::Vector2f(x, part.getPosition().y));
}

sf::Vector2f Background::getPosition() const
{
	if(backgroundParts.size() <= 0)
		return sf::Vector2f(0, 0);
	else
		return backgroundParts[0].getPosition();
}

void Background::move(sf::Vector2f pos)
{
	for(auto &part: backgroundParts)
		part.move(pos);
}

sf::FloatRect Background::getGlobalBounds() const
{
	if(backgroundParts.size() < 0)
		return sf::FloatRect();
	else
		return backgroundParts[0].getGlobalBounds();
}

// ---BackgroundController---
BackgroundController::BackgroundController(const sf::Texture &mountains, const sf::Texture &forest, const sf::Texture &field)
{
	for(int i = 0; i < backgroundSprites.size(); ++i) {
		backgroundSprites[i] = std::make_unique<Background>(mountains, forest, field);
		if(i > 0)
			backgroundSprites[i]->setPositionX(backgroundSprites[i - 1]->getGlobalBounds().left + backgroundSprites[i - 1]->getGlobalBounds().width);
		else 
			backgroundSprites[i]->setPositionX(0.f);
	}
	spriteWidth = backgroundSprites[0]->getGlobalBounds().width;
}

void BackgroundController::move(sf::Vector2f offset)
{
	if(offset == sf::Vector2f(0, 0)) return;

	for(auto &item: backgroundSprites)
		item->move(sf::Vector2f(0, offset.y));
	globalCameraOffsetX += offset.x;
	
	if(globalCameraOffsetX / spriteWidth > 2) {
		globalCameraOffsetX -= spriteWidth;
		std::rotate(backgroundSprites.begin(), backgroundSprites.begin() + 1, backgroundSprites.end());
		// backgroundSprites.back().setPosition(sf::Vector2f(backgroundSprites[backgroundSprites.size() - 2].getGlobalBounds().left + spriteWidth,
		// 												  backgroundSprites[0].getPosition().y));
		backgroundSprites.back()->setPositionX(backgroundSprites[backgroundSprites.size() - 2]->getGlobalBounds().left + spriteWidth);
	}

}

void BackgroundController::draw(sf::RenderWindow &window)
{
	for(auto &item: backgroundSprites)
		item->draw(window);
}
