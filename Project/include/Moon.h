#pragma once

#include "Entity.h"

class Moon : public Entity
{
public:
    Moon();

protected:
    virtual void DefineFixture(const sf::Vector2u textureSize) override;
};