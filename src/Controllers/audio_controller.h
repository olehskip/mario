#include <memory>
#include <list>

#include "../Loaders/audio_loader.h"

class AudioController
{
public:
	AudioController();
	void startPlayingMusic();

	void toggleMute();
	void mute();
	void unmute();
	
	// If currrent music ended, then this function start playing the next one
	void update();

private:
	bool isMuted = false;
	AudioLoader audioLoader;
	size_t currentMusicIndex;
};
