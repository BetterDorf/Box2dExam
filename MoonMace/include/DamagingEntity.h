#pragma once
#include "Entity.h"

#include <SFML/Audio/Sound.hpp>


class DamagingEntity : public Entity
{
public:
	DamagingEntity(Game& gameRef, int id, float strengthMod, int value);

	int GetId();

	void Init(float x, float y, const SpritePath& spritePath = SpritePath::StarEnemy) override;
	void DefineFixture(const sf::Vector2u textureSize) override;
	void Update() override;

	void Die();

private:
	int id_;
	float strengthMod_ = 1.0f;
	int value_ = 1;

	sf::Sound sound_;
};