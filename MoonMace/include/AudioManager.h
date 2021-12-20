#pragma once
#include <SFML/Audio.hpp>
#include <AudioPathes.h>
#include <map>

//Holds the sounds buffers and plays music
class AudioManager
{
public:
	AudioManager();
	static AudioManager* GetInstance() { return instance_; }

	void PlayMusic();
	sf::SoundBuffer& RequestBuffer(AudioPath path);

protected:
	static AudioManager* instance_;

private:
	std::map<std::string, sf::SoundBuffer> buffers_;
	sf::Music music_;
};