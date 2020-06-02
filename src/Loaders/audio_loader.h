#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <memory>
#include <vector>
#include <unordered_map>

#include "loader_interface.h"

// ---music----

/* 
 * ---All music---
 * super_mario_bros
 * hurry
 */

class MusicObject: public LoaderObjectInterface<sf::Music>
{
public:
	MusicObject(const std::string &musicPath);
};


class MusicLoader: public LoaderInterface<sf::Music>
{
public:
	MusicLoader();
};

// --sounds---

/*
 * ---All sounds---
 * mario_dies
 * mario_jumps
 */

class SoundObject: public LoaderObjectInterface<sf::SoundBuffer>
{
public:
	SoundObject(const std::string &soundPath);
};


class SoundsLoader: public LoaderInterface<sf::SoundBuffer>
{
public:
	SoundsLoader();
};
