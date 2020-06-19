#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Color.hpp>


class FPS
{ 
public:
	void update();
	unsigned int getFPS() const;
	sf::Color getColor() const;

private:
	unsigned int mFrame;
	unsigned int mFPS;
	sf::Clock mClock;
};
