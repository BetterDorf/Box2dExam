#pragma once

#include <string>

enum class AudioPath
{
	StarSpawn,
	Explosion,
	GameOver1,
	GameOver2,
	GameOver3,
	GameOver4,
	Bounce
};

std::string ConvertPathToString(AudioPath path);