#include "audio_controller.h"

AudioController::AudioController()
{
	jumpSound.setBuffer(soundsLoader.getObject("mario_jumps"));
	dieSound.setBuffer(soundsLoader.getObject("mario_dies"));
}

void AudioController::startPlayingMusic()
{
	currentMusicIndex = 0;
	musicLoader.getObject(currentMusicIndex).play();
	musicLoader.getObject(currentMusicIndex).setVolume(volume);
}

void AudioController::playSound(const std::string &soundName)
{
	jumpSound.stop();
	jumpSound.setVolume(100);
	jumpSound.play();
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
		musicLoader.getObject(currentMusicIndex).play();
		musicLoader.getObject(currentMusicIndex).setVolume(volume);
	}
}