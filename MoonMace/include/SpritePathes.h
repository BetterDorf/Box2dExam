#pragma once
#include <string>

enum class SpritePath
{
	Player,
	StarEnemy,
	Chain,
	Moon
};

std::string ConvertPathToString(SpritePath path);