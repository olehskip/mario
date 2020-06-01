#include "game_object.h"

// ---GameObject---
GameObject::GameObject(sf::Vector2f pos, sf::Vector2f _scale, const sf::Texture &_texture):
	texture(_texture)
{	
	sprite.setTexture(texture);
	sprite.setPosition(pos.x, pos.y);
	sprite.scale(_scale.x, _scale.y);
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

void GameObject::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

// ---BotGameObject---
// BotGameObject::BotGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, sf::Vector2f _acceleration, sf::Vector2f _deceleration, sf::Vector2f _maxAcceleration): 
// 	LiveGameObject(pos, scale, _texture, _acceleration, _deceleration,_maxAcceleration)
// {

// }