#pragma once

#include <string>

enum class AudioPath
{
	StarSpawn,
	Explosion
};

std::string ConvertPathToString(AudioPath path);