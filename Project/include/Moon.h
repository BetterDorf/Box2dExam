#pragma once

#include "Entity.h"

class Moon : public Entity
{
protected:
    virtual void DefineFixture(const b2Vec2 textureSize) override;
public:
    using Entity::Entity;
};