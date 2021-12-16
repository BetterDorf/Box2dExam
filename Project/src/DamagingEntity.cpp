#include "DamagingEntity.h"
#include "GameplayConstants.h"

#include "game.h"

void DamagingEntity::Init(float x, float y, const std::string& spritePath, Tag tag)
{
	Entity::Init(x, y, spritePath, tag);

	b2Vec2 destination = Game::GetInstance()->GetPlayerPos() - body_->GetPosition();
	destination.Normalize();

	destination *= ENEMY_IMPULSE;
	body_->ApplyForceToCenter(destination, true);
}

void DamagingEntity::DefineFixture(const b2Vec2 textureSize)
{
    b2PolygonShape hitBox;
    hitBox.SetAsBox(0.5f * textureSize.x, 0.5f * textureSize.y);

    b2FixtureDef enemyFixtureDef;
    enemyFixtureDef.shape = &hitBox;
    enemyFixtureDef.friction = 0.0f;
    enemyFixtureDef.restitution = 1.0f;
    enemyFixtureDef.density = 1.0f;

    body_->SetLinearDamping(0.1f);
    body_->CreateFixture(&enemyFixtureDef);
}

void DamagingEntity::Update()
{
    Entity::Update();

    //Apply force each frame
    b2Vec2 destination = Game::GetInstance()->GetPlayerPos() - body_->GetPosition();
    destination.Normalize();

    destination *= ENEMY_ACCEL;
    body_->ApplyForceToCenter(destination, true);
}
