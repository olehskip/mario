#include "audio_loader.h"

// ---music---
// ---MusicObject---
MusicObject::MusicObject(const std::string &musicPath):
	LoaderObjectInterface(musicPath)
{
	object.openFromFile(musicPath);
	object.setVolume(100);
}

// ---MusicLoader---+
MusicLoader::MusicLoader()
{
	allObjects.insert(std::make_pair(MusicID::SUPER_MARIO_BROS3, std::make_unique<MusicObject>("data/audio/music/super_mario_bros3.ogg")));
	allObjects.insert(std::make_pair(MusicID::SUPER_MARIO_BROS2, std::make_unique<MusicObject>("data/audio/music/super_mario_bros2.ogg")));
	allObjects.insert(std::make_pair(MusicID::HURRY, std::make_unique<MusicObject>("data/audio/music/hurry.ogg")));
	allObjects.insert(std::make_pair(MusicID::SUPER_MARIO_BROS, std::make_unique<MusicObject>("data/audio/music/super_mario_bros.ogg")));
}

// ---sounds---
// ---SoundObject---
SoundObject::SoundObject(const std::string &soundPath):
	LoaderObjectInterface(soundPath)
{
	buffer->loadFromFile(soundPath);
	object.setBuffer(*buffer);
}

// ---SoundsLoader---
SoundsLoader::SoundsLoader()
{
	allObjects.insert(std::make_pair(SoundsID::MARIO_JUMPS, std::make_unique<SoundObject>("data/audio/sounds/mario_jumps.ogg")));
	allObjects.insert(std::make_pair(SoundsID::MARIO_DIES, std::make_unique<SoundObject>("data/audio/sounds/mario_dies.ogg")));
}


