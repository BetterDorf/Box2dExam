#include "Rope.h"

#include "SFML_Utilities.h"

Rope::Rope(Game& gameRef) : Entity(CollisionTag::IGNORE, gameRef)
{
	
}


void Rope::DefineFixture(const sf::Vector2u textureSize)
{
    b2PolygonShape hitBox;
    hitBox.SetAsBox(0.5f * pixelsToMeters(textureSize.x), 0.5f * pixelsToMeters(textureSize.y));

    b2FixtureDef ropeFixtureDef;
    ropeFixtureDef.shape = &hitBox;
    ropeFixtureDef.density = 0.4f;
    ropeFixtureDef.friction = 0.0f;
    //ropeFixtureDef.isSensor = true;

    body_->CreateFixture(&ropeFixtureDef);
}
