#pragma once
#include <string>

enum class SpritePath
{
	Player,
	StarEnemy,
	Chain,
	Moon,
	Explosion,
	Rocket
};

std::string ConvertPathToString(SpritePath path);