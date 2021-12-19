#pragma once

#include "Entity.h"

class Moon : public Entity
{
public:
    Moon(Game& gameRef);
    void Init(float x, float y, const SpritePath& spritePath = SpritePath::Moon) override { Entity::Init(x, y, spritePath); }

protected:
    void DefineFixture(const sf::Vector2u textureSize) override;
};