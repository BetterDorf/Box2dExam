#include "AudioPathes.h"

#include <iostream>

std::string ConvertPathToString(AudioPath path)
{
	std::string base = "data/Audio/";

	switch (path)
	{
	case AudioPath::StarSpawn: return base + "StarSpawn.ogg";
	default: std::cerr << "Audio path is incorrect. Somehow." << std::endl;
	}
}
