#pragma once
#include <SFML/Audio.hpp>

//Holds the sounds buffers and plays music
class AudioManager
{
public:
	AudioManager();
	static AudioManager* GetInstance() { return instance_; }

	void PlayMusic();

protected:
	static AudioManager* instance_;

private:
	sf::Music music_;
};