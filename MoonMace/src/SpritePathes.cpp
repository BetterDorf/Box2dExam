#include "SpritePathes.h"

std::string ConvertPathToString(SpritePath path)
{
	std::string base = "data/Sprites/";

	switch (path)
	{
	case SpritePath::Player:
		return base + "Ship.png";
	case SpritePath::StarEnemy:
		return base + "StarShip.png";
	case SpritePath::Chain:
		return base + "Chain.png";
	case SpritePath::Moon:
		return base + "Moon.png";
	}
}