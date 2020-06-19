#include "fps.h"


void FPS::update()
{
	if(mClock.getElapsedTime().asSeconds() >= 1.f)
	{
		mFPS = mFrame;
		mFrame = 0;
		mClock.restart();
	}

	++mFrame;
}
unsigned int FPS::getFPS() const 
{
	return mFPS; 
}

sf::Color FPS::getColor() const
{
	if(mFPS > 40)
		return sf::Color::Green;
	else if(mFPS < 20)
		return sf::Color::Red;
	else
		return sf::Color::Yellow;
}
