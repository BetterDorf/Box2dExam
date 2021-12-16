#include "DamagingEntity.h"
#include "GameplayConstants.h"

#include "game.h"
#include "SFML_Utilities.h"

DamagingEntity::DamagingEntity(int id) : Entity(CollisionTag::DAMAGING), id_(id)
{
	
}

int DamagingEntity::GetId()
{
    return id_;
}


void DamagingEntity::Init(float x, float y, const std::string& spritePath)
{
	Entity::Init(x, y, spritePath);

	b2Vec2 destination = Game::GetInstance()->GetPlayerPos() - body_->GetPosition();
	destination.Normalize();

	destination *= ENEMY_IMPULSE;
	body_->ApplyForceToCenter(destination, true);
}

void DamagingEntity::DefineFixture(const sf::Vector2u textureSize)
{
    b2PolygonShape hitBox;
    hitBox.SetAsBox(0.5f * pixelsToMeters(textureSize.x), 0.5f * pixelsToMeters(textureSize.y));

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
