#include "game_object.h"

GameObject::GameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture):
	texture(_texture)
{	
	sprite.setTexture(texture);
	sprite.setPosition(pos.x, pos.y);
	sprite.scale(scale.x, scale.y);
}

sf::Vector2f GameObject::getPosition() const
{
	return sprite.getPosition();
}

sf::FloatRect GameObject::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void GameObject::setPosition(sf::Vector2f newPos)
{
	sprite.setPosition(newPos);
}

sf::Vector2f GameObject::getOffset() const
{
	return offset;
}

void GameObject::setOffset(sf::Vector2f newOffset)
{
	offset = newOffset;
}

void GameObject::draw(sf::RenderWindow &window)
{
	sprite.move(offset);
	window.draw(sprite);
}

bool GameObject::isNeedToRemove() const
{
	return mIsNeedToRemove;
}