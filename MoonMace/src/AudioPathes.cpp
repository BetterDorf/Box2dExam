#include "AudioPathes.h"

#include <iostream>

std::string ConvertPathToString(AudioPath path)
{
	std::string base = "data/Audio/";

	switch (path)
	{
	case AudioPath::StarSpawn: return base + "StarSpawn.ogg";
	case  AudioPath::Explosion: return base + "Explosion.ogg";
	case AudioPath::GameOver1: return base + "GameOver1.ogg";
	case AudioPath::GameOver2: return base + "GameOver2.ogg";
	case AudioPath::GameOver3: return base + "GameOver3.ogg";
	case AudioPath::GameOver4: return base + "GameOver4.ogg";
	case AudioPath::Bounce: return base + "Bounce.ogg";
	default: std::cerr << "Audio path doesn't exist. Somehow." << std::endl;
	}
}
