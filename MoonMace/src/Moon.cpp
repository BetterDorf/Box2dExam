#include "Moon.h"

#include "SFML_Utilities.h"

Moon::Moon(Game& gameRef) : Entity(CollisionTag::MOON, gameRef)
{
	
}

void Moon::DefineFixture(const sf::Vector2u textureSize)
{
    b2CircleShape hitBox;
    hitBox.m_radius = pixelsToMeters(textureSize.x) * 0.5f;

    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 0.2f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.6f;

    body_->CreateFixture(&playerFixtureDef);
}