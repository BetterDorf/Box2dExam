#pragma once
#include <string>

enum class SpritePath
{
	Player,
	StarEnemy,
	Chain,
	Moon,
	Explosion
};

std::string ConvertPathToString(SpritePath path);