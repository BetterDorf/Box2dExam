#include "SpritePathes.h"

std::string ConvertPathToString(SpritePath path)
{
	switch (path)
	{
	case SpritePath::Player:
		return "data/Ship.png";
	case SpritePath::StarEnemy:
		return "data/StarShip.png";
	case SpritePath::Chain:
		return "data/Chain.png";
	case SpritePath::Moon:
		return "data/Moon.png";
	}
}