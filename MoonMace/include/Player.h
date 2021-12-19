#pragma once

#include "Entity.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "GameplayConstants.h"

class Player : public Entity
{
public:
	Player();

	void Init(float x, float y, const SpritePath& spritePath = SpritePath::Player) override { Entity::Init(x, y, spritePath); }
	void Rotate(bool right);
	void Accelerate();
	void Deccelerate();
	void DeccelRotate();

	void Update() override;

protected:
	void DefineFixture(const sf::Vector2u textureSize) override;

private:
	const float speed = 1.0f;
	const float max_speed = MAX_SPEED;

	const float turning_speed = ROT_SPEED * M_PI;
	const float max_turn_speed = MAX_ROT_SPEED * M_PI;

	const float moving_damp = 0.5f;
	const float stopped_damp = 4.0f;

}; 