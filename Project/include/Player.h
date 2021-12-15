#pragma once

#include "Entity.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "GameplayConstants.h"

class Player : public Entity
{
protected:
	void DefineFixture(const b2Vec2 textureSize) override;
private:
	const float speed = 1.0f;
	const float max_speed = MAX_SPEED;

	const float turning_speed = ROT_SPEED * M_PI;
	const float max_turn_speed = MAX_ROT_SPEED * M_PI;

	const float moving_damp = 0.5f;
	const float stopped_damp = 4.0f;

public:
	Player() = default;

	void Rotate(bool right);
	void Accelerate();
	void Deccelerate();
	void DeccelRotate();
}; 