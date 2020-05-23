#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <array>

#include "textures.h"

class BackgroundController
{
public:
    BackgroundController();

    void move(sf::Vector2f offset);
    void draw(sf::RenderWindow &window);

private:
    std::array<sf::Sprite, 3> backgroundSprites;

    float globalCameraOffsetX = 0.f;
    float spriteWidth;
};