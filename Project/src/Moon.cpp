#include "Moon.h"

Moon::Moon() : Entity(CollisionTag::MOON)
{
	
}

void Moon::DefineFixture(const b2Vec2 textureSize)
{
    b2CircleShape hitBox;
    hitBox.m_radius = textureSize.x * 0.5f;

    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 0.2f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.6f;

    body_->CreateFixture(&playerFixtureDef);
}