#include "audio_loader.h"

// ---MusicObject---
MusicObject::MusicObject(const std::string &musicPath)
{
	music->openFromFile(musicPath);
	music->setVolume(100);
	music->setLoop(true); // temponary
}

// ---AudioLoader---
AudioLoader::AudioLoader()
{
	allMusic.push_back(MusicObject("data/audio/music/super_mario_bros.ogg"));
	allMusic.push_back(MusicObject("data/audio/music/hurry.ogg"));
	allMusic.push_back(MusicObject("data/audio/music/game_over.ogg"));
}

const std::shared_ptr<sf::Music> AudioLoader::getMusic(MusicID musicID) const
{
	return allMusic[static_cast<int>(musicID)].music;
}
