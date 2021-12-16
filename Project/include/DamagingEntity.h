#pragma once
#include "Entity.h"

class DamagingEntity : public Entity
{
public:
	DamagingEntity(int id) { id_ = id; }
	void Init(float x, float y, const std::string& spritePath = "data/Rope.png", Tag tag = Tag::DAMAGING) override;
	void DefineFixture(const b2Vec2 textureSize) override;
	void Update() override;
};