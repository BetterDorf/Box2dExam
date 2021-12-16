#include "Player.h"

#include <SFML_utilities.h>

Player::Player() : Entity(CollisionTag::PLAYER)
{
	
}


void Player::Rotate(bool right)
{
	body_->SetAngularDamping(moving_damp);
	if (right && body_->GetAngularVelocity() > -max_turn_speed || !right && body_->GetAngularVelocity() < max_turn_speed)
	{
		float sign = 1;
		if (right)
			sign = -1;
		body_->ApplyTorque(turning_speed * sign, true);
	}
}

void Player::Accelerate()
{
	body_->SetLinearDamping(moving_damp);
	
	float curSpeed = body_->GetLocalVector(body_->GetLinearVelocity()).y;

	if (curSpeed < max_speed)
	{
		b2Vec2 localForce(0.0f, speed);
		b2Vec2 worldForce = body_->GetWorldVector(localForce);

		body_->ApplyForceToCenter(worldForce, true);
	}
}

void Player::Deccelerate()
{
	body_->SetLinearDamping(stopped_damp);
}

void Player::DeccelRotate()
{
	body_->SetAngularDamping(stopped_damp);
}

void Player::DefineFixture(const sf::Vector2u textureSize)
{
	b2CircleShape hitBox;
	hitBox.m_radius = pixelsToMeters(textureSize.x) / 3.0f;

	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &hitBox;
	playerFixtureDef.friction = 1.0f;
	playerFixtureDef.restitution = 0.0f;
	playerFixtureDef.density = 2.0f;

	body_->CreateFixture(&playerFixtureDef);
}
