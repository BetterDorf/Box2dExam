#pragma once
#include "Entity.h"

class DamagingEntity : public Entity
{
public:
	DamagingEntity(int id);

	int GetId();

	void Init(float x, float y, const std::string& spritePath = "data/Rope.png") override;
	void DefineFixture(const sf::Vector2u textureSize) override;
	void Update() override;

private:
	int id_;
};