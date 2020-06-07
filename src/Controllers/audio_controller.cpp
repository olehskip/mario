#include "audio_controller.h"

AudioController::AudioController()
{
}

void AudioController::startPlayingMusic()
{
	musicLoader.getObject(currentMusicIndex).stop();
	currentMusicIndex = 0;
	isStoppedMusic = false;
	musicLoader.getObject(currentMusicIndex).play();
	musicLoader.getObject(currentMusicIndex).setVolume(volume);
	for(auto currentSoundID: currentSoundsID)
		soundsLoader.getObject(currentSoundID).stop();
}

void AudioController::stopPlayingMusic()
{
	isStoppedMusic = true;
	musicLoader.getObject(currentMusicIndex).stop();
}

void AudioController::playSound(SoundsID soundID)
{
	soundsLoader.getObject(soundID).setVolume(volume);
	soundsLoader.getObject(soundID).play();
	currentSoundsID.push_back(soundID);
}

bool AudioController::toggleMute()
{
	if(volume == 100)
		mute();
	else
		unmute();
	
	return volume != 100;
}

void AudioController::mute()
{
	volume = 0;
	musicLoader.getObject(currentMusicIndex).setVolume(volume);
	for(auto currentSoundID: currentSoundsID)
		soundsLoader.getObject(currentSoundID).setVolume(volume);
}

void AudioController::unmute()
{
	volume = 100;
	musicLoader.getObject(currentMusicIndex).setVolume(volume);
	for(auto currentSoundID: currentSoundsID)
		soundsLoader.getObject(currentSoundID).setVolume(volume);	
}

void AudioController::update()
{
	for(auto itt = currentSoundsID.rbegin(); itt != currentSoundsID.rend(); ++itt) {
		if(soundsLoader.getObject(*itt).getStatus() == sf::SoundStream::Status::Stopped)
			currentSoundsID.erase(std::remove(currentSoundsID.begin(), currentSoundsID.end(), *itt));
	}

	if(!isStoppedMusic && musicLoader.getObject(currentMusicIndex).getStatus() == sf::SoundStream::Status::Stopped) {
		musicLoader.getObject(currentMusicIndex).stop();
		if(++currentMusicIndex > musicLoader.getCount())
			currentMusicIndex = 0;
		musicLoader.getObject(currentMusicIndex).play();
		musicLoader.getObject(currentMusicIndex).setVolume(volume);
	}
}
