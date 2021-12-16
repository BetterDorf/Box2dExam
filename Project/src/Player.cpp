#include "Player.h"

#include <iostream>
#include <SFML_utilities.h>

#include "game.h"

Player::Player() : Entity(CollisionTag::PLAYER)
{}


void Player::Update()
{
	Entity::Update();

	//Prevent the player from going out of the map by making him bounce
	b2Vec2 window = pixelsToMeters(Game::GetInstance()->getWindow().getSize());
	b2Vec2 pos = body_->GetPosition();
	b2Vec2 veloc = body_->GetLinearVelocity();

	//Distance to the edge when we bounce
	float buffer = pixelsToMeters(getTextureRect().width) / 2.0f;

	if ((pos.x > window.x && veloc.x > buffer) || (pos.x < buffer && veloc.x < 0))
	{
		body_->SetLinearVelocity(b2Vec2(-veloc.x, veloc.y));
	}
	if ((pos.y > window.y && veloc.y > buffer) || (pos.y < buffer && veloc.y < 0))
	{
		body_->SetLinearVelocity(b2Vec2(veloc.x, -veloc.y));
	}
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
