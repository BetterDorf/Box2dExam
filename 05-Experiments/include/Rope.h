#include "Entity.h"

class Rope : public Entity
{
	using Entity::Entity;

	void DefineFixture(const b2Vec2 textureSize) override;
};