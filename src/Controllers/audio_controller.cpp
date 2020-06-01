#include "audio_controller.h"

AudioController::AudioController()
{
}

void AudioController::startPlayingMusic()
{
	currentMusicIndex = 0;
}

void AudioController::playSound(const std::string &soundName)
{
}

void AudioController::toggleMute()
{
	if(volume == 100)
		mute();
	else
		unmute();
}

void AudioController::mute()
{
	volume = 0;
	musicLoader.getObject(currentMusicIndex).setVolume(0);
}

void AudioController::unmute()
{
	volume = 100;
	musicLoader.getObject(currentMusicIndex).setVolume(100);
}

void AudioController::update()
{
	if(musicLoader.getObject(currentMusicIndex).getStatus() == sf::SoundStream::Status::Stopped) {
		musicLoader.getObject(currentMusicIndex).stop();
		if(++currentMusicIndex > musicLoader.getCount())
			currentMusicIndex = 0;
		// musicLoader.getObject(currentMusicIndex).play();
		musicLoader.getObject(currentMusicIndex).setVolume(volume);
	}
}