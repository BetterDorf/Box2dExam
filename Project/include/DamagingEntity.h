#pragma once
#include "Entity.h"

class DamagingEntity : public Entity
{
public:
	DamagingEntity(int id) { id_ = id; }
	void Init(const std::string& spritePath, float x, float y, Tag tag = Tag::DAMAGING) override;
	void DefineFixture(const b2Vec2 textureSize) override;
};