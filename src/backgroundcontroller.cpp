#include "backgroundcontroller.h"

BackgroundController::BackgroundController()
{
	for(int i = 0; i < backgroundSprites.size(); ++i) {
		backgroundSprites[i].setTexture(*textures.getTexture(TexturesID::GRASSY_BACKGROUND));
		backgroundSprites[i].setScale(sf::Vector2f(1, float(backgroundSprites[i].getTexture()->getSize().y / config::WINDOW_HEIGHT) + 0.1));
		if(i > 0)
			backgroundSprites[i].setPosition(backgroundSprites[i - 1].getGlobalBounds().left + backgroundSprites[i - 1].getGlobalBounds().width, 0);
		else 
			backgroundSprites[i].setPosition(0, 0);
	}
	spriteWidth = backgroundSprites[0].getGlobalBounds().width;
}

void BackgroundController::move(sf::Vector2f offset)
{
	if(offset == sf::Vector2f(0, 0)) return;

	for(auto &item: backgroundSprites)
    	item.move(0, offset.y);
	globalCameraOffsetX += offset.x;
	
	if(globalCameraOffsetX / spriteWidth > 2) {
		globalCameraOffsetX -= spriteWidth;
		std::rotate(backgroundSprites.begin(), backgroundSprites.begin() + 1, backgroundSprites.end());
		backgroundSprites.back().setPosition(sf::Vector2f(backgroundSprites[backgroundSprites.size() - 2].getGlobalBounds().left + spriteWidth,
														  backgroundSprites[0].getPosition().y));
	}

}

void BackgroundController::draw(sf::RenderWindow &window)
{
	for(auto &item: backgroundSprites)
    	window.draw(item);
}
