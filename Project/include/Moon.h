#pragma once

#include "Entity.h"

class Moon : public Entity
{
public:
    Moon();

protected:
    virtual void DefineFixture(const b2Vec2 textureSize) override;
};