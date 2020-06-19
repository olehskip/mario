#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <memory>
#include <thread>


class LabelController
{
public:
	LabelController(sf::Vector2f pos, const sf::Font &font, unsigned int fontSize, sf::Color color, const std::string &text);
	void setText(const std::string &text);
	std::string getText() const;

	void toCenterX(float windowWidth);
	void toCenterY(float windowHeight);
	void toTopY();
	void toBottomY(float windowHeight);
	float getOrigin() {
		return textObj.getOrigin().y;
	}
	void centerOrigin();
	void centerOriginX();
	void centerOriginY();
	void setPosition(const sf::Vector2f &pos);
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	void move(const sf::Vector2f &pos);
	
	void blink(bool blinkState, float delay = 0.f);

	virtual void draw(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window, sf::Color color);

protected:
	sf::Text textObj;

	bool isVisible = true;
	bool isBlinking = false;
	float blinkDelay = 0.f;
	sf::Clock blinkingClock;
};
typedef std::unique_ptr<LabelController> Label_ptr;
