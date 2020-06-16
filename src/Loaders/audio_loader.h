#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <memory>
#include <vector>
#include <unordered_map>

#include "loader_interface.h"

// ---music----
enum class MusicID
{
	SUPER_MARIO_BROS,
	SUPER_MARIO_BROS2,
	SUPER_MARIO_BROS3,
	HURRY
};

class MusicObject: public LoaderObjectInterface<sf::Music>
{
public:
	MusicObject(const std::string &musicPath);
};

class MusicLoader: public LoaderInterface<sf::Music, MusicID>
{
public:
	MusicLoader();
};


// --sounds---
enum class SoundsID
{
	MARIO_JUMPS,
	MARIO_DIES,
	MARIO_STOMPS
};

class SoundObject: public LoaderObjectInterface<sf::Sound>
{
public:
	SoundObject(const std::string &soundPath);

private:
	std::unique_ptr<sf::SoundBuffer> buffer = std::make_unique<sf::SoundBuffer>();
};

class SoundsLoader: public LoaderInterface<sf::Sound, SoundsID>
{
public:
	SoundsLoader();
};
