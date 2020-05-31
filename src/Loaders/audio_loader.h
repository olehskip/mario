#pragma once

#include "loader_interface.h"
#include <SFML/Audio/Music.hpp>
#include <iostream>
#include <memory>
#include <vector>

enum class MusicID
{
	SUPER_MARIO_BROS,
	HURRY,
	GAME_OVER
};

class MusicObject
{
public:
	MusicObject(const std::string &musicPath);
	std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
};

/*
 * AudioLoader doesn't need Singleton pattern,
 * because only AudioController has access and controls the music
 */
class AudioLoader
{
public:
	AudioLoader();
	const std::shared_ptr<sf::Music> getMusic(MusicID musicID) const;

private:
	std::vector<MusicObject> allMusic;
};
