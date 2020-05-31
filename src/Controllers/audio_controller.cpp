#include "audio_controller.h"

AudioController::AudioController()
{
	
}

void AudioController::startPlayingMusic()
{
	audioLoader.getMusic(MusicID::SUPER_MARIO_BROS)->setVolume(100);
	audioLoader.getMusic(MusicID::SUPER_MARIO_BROS)->play();
}

void AudioController::toggleMute()
{
	isMuted = !isMuted;
	if(isMuted)
		mute();
	else
		unmute();
}

void AudioController::mute()
{
	isMuted = true;
	audioLoader.getMusic(MusicID::SUPER_MARIO_BROS)->setVolume(0);
}

void AudioController::unmute()
{
	isMuted = false;
	audioLoader.getMusic(MusicID::SUPER_MARIO_BROS)->setVolume(100);
}

void AudioController::update()
{
}