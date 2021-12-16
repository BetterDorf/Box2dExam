#include "Rope.h"

void Rope::DefineFixture(const b2Vec2 textureSize)
{
    b2PolygonShape hitBox;
    hitBox.SetAsBox(0.5f * textureSize.x, 0.5f * textureSize.y);

    b2FixtureDef ropeFixtureDef;
    ropeFixtureDef.shape = &hitBox;
    ropeFixtureDef.density = 0.4f;
    ropeFixtureDef.friction = 0.0f;
    //ropeFixtureDef.isSensor = true;

    body_->CreateFixture(&ropeFixtureDef);
}