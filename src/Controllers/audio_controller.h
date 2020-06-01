#include <SFML/Audio/Sound.hpp>
#include <memory>
#include <list>

#include "../Loaders/audio_loader.h"

enum class SoundType
{
	MARIO_JUMP,
	MARIO_DIES
};

class AudioController
{
public:
	AudioController();
	void startPlayingMusic();
	void playSound(const std::string &soundName);

	void toggleMute();
	void mute();
	void unmute();
	// sf::Sound jumpSound;
	
	// If currrent music ended, then this function start playing the next one
	void update();

private:
	MusicLoader musicLoader;
	SoundsLoader soundsLoader;

	size_t currentMusicIndex = 0;
	unsigned int volume = 100;
};
