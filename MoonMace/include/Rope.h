#include "Entity.h"

class Rope : public Entity
{
public:
	Rope(Game& gameRef);
	void Init(float x, float y, const SpritePath& spritePath = SpritePath::Chain) override { Entity::Init(x, y, spritePath); }

protected:
	void DefineFixture(const sf::Vector2u textureSize) override;
};