#include "AudioManager.h"

#include <iostream>

AudioManager* AudioManager::instance_ = nullptr;

AudioManager::AudioManager()
{
	instance_ = this;

	music_.setVolume(40);
}

sf::SoundBuffer& AudioManager::RequestBuffer(AudioPath path)
{
	std::string audioPath = ConvertPathToString(path);

	//Add the audio to the map of loaded buffers if it wasn't already in there
	if (!buffers_.contains(audioPath))
	{
		sf::SoundBuffer buffer;
		buffer.loadFromFile(audioPath);

		//Check for incorrect path
		if (buffer.getSampleCount() == 0)
		{
			std::cerr << "Audio Path is incorrect : " + audioPath << std::endl;
		}

		buffers_.emplace(audioPath, buffer);
	}

	return buffers_.at(audioPath);
}


void AudioManager::PlayMusic()
{
	//Hardcoded for now
	if (!music_.openFromFile("data/Music/Shelf_Space.ogg"))
		return;

	music_.play();
	music_.setLoop(true);
}