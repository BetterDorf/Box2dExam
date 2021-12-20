#include "AudioManager.h"

AudioManager* AudioManager::instance_ = nullptr;

AudioManager::AudioManager()
{
	instance_ = this;

	music_.setVolume(40);
}

void AudioManager::PlayMusic()
{
	//Hardcoded for now
	if (!music_.openFromFile("data/Music/Shelf_Space.ogg"))
		return;

	music_.play();
}