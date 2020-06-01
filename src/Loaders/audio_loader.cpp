#include "audio_loader.h"

// ---music---
// ---MusicObject---
MusicObject::MusicObject(const std::string &musicPath):
	LoaderObjectInterface(musicPath)
{
	object->openFromFile(musicPath);
	object->setVolume(100);
}

// ---MusicLoader---
MusicLoader::MusicLoader()
{
	allObjects.insert(std::make_pair("hurry", MusicObject("data/audio/music/hurry.ogg")));
	allObjects.insert(std::make_pair("super_mario_bros", MusicObject("data/audio/music/super_mario_bros.ogg")));
}

// ---sounds---
// ---SoundObject---
SoundObject::SoundObject(const std::string &soundPath): LoaderObjectInterface(soundPath)
{
	object->loadFromFile(soundPath);
	// object->setBuffer(soundBuffer);
	// object->setVolume(100);
}

// ---SoundsLoader---
SoundsLoader::SoundsLoader()
{
	allObjects.insert(std::make_pair("mario_jumps", SoundObject("data/audio/sounds/mario_jumps.ogg")));
	allObjects.insert(std::make_pair("mario_dies", SoundObject("data/audio/sounds/mario_dies.ogg")));
}
