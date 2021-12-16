#include "Entity.h"

class Rope : public Entity
{
	using Entity::Entity;

	void DefineFixture(const sf::Vector2u textureSize) override;
};