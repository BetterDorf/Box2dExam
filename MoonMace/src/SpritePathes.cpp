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
	case SpritePath::StarEnemy2:
		return base + "StarShip2.png";
	case SpritePath::Chain:
		return base + "Chain.png";
	case SpritePath::Moon:
		return base + "Moon.png";
	case SpritePath::Explosion:
		return base + "Explosion-Sheet.png";
	case SpritePath::Rocket :
		return base + "Rocket.png";
	}
}