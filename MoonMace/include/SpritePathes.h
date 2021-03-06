#pragma once
#include <string>

enum class SpritePath
{
	Player,
	StarEnemy,
	StarEnemy2,
	Chain,
	Moon,
	Explosion,
	Rocket,
	Capsule
};

std::string ConvertPathToString(SpritePath path);