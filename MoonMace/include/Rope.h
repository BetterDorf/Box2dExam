#include "Entity.h"

class Rope : public Entity
{
public:
	void Init(float x, float y, const SpritePath& spritePath = SpritePath::Chain) override { Entity::Init(x, y, spritePath); }
	using Entity::Entity;

protected:
	void DefineFixture(const sf::Vector2u textureSize) override;
};