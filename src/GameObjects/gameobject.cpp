#include "gameobject.h"

// ---GameObject---
GameObject::GameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture)
{
	texture = _texture;
	
	sprite.setTexture(*texture);
	sprite.setPosition(pos.x, pos.y);
	sprite.scale(scale.x, scale.y);
}

sf::Texture GameObject::getTextureCopy() const
{
	return *texture;
}

sf::Sprite GameObject::getSpriteCopy() const
{
	return sprite;
}

void GameObject::setPosition(sf::Vector2f newPos)
{
	sprite.setPosition(newPos);
}

sf::Vector2f GameObject::getOffset() const
{
	return offset;
}

sf::Vector2f GameObject::getGlobalOffset() const
{
	return globalOffset;
}

void GameObject::update(sf::RenderWindow &window, float time)
{
	updateMovement(time);
	draw(window);
}

void GameObject::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
	globalOffset += offset;
}

// ---LiveGameObject---
LiveGameObject::LiveGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, sf::Vector2f _accelaration, sf::Vector2f _deceleration, sf::Vector2f _maxAccelaration): 
	GameObject(pos, scale, _texture), accelaration(_accelaration), deceleration(_deceleration), maxAccelaration(_maxAccelaration)
{
}

// ---BotGameObject---
BotGameObject::BotGameObject(sf::Vector2f pos, sf::Vector2f scale, std::shared_ptr<sf::Texture> _texture, sf::Vector2f _accelaration, sf::Vector2f _deceleration, sf::Vector2f _maxAccelaration): 
	LiveGameObject(pos, scale, _texture, _accelaration, _deceleration,_maxAccelaration)
{

}