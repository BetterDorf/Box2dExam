#include "DamagingEntity.h"
#include "GameplayConstants.h"

#include "Game.h"
#include "SFML_Utilities.h"
#include "AudioManager.h"
#include "AudiovisualEffect.h"

DamagingEntity::DamagingEntity(Game& gameRef, int id, float strengthMod, int value) : Entity(CollisionTag::DAMAGING, gameRef),
id_(id), strengthMod_(strengthMod), value_(value)
{}

int DamagingEntity::GetId()
{
    return id_;
}


void DamagingEntity::Init(float x, float y, const SpritePath& spritePath)
{
	Entity::Init(x, y, spritePath);

	b2Vec2 destination = gameRef_.GetPlayerPos() - body_->GetPosition();
	destination.Normalize();

	destination *= ENEMY_IMPULSE;
	body_->ApplyForceToCenter(destination, true);

    //Play the creation sound
    sound_.setBuffer(AudioManager::GetInstance()->RequestBuffer(AudioPath::StarSpawn));
    sound_.play();
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
    b2Vec2 destination = gameRef_.GetPlayerPos() - body_->GetPosition();
    destination.Normalize();

    destination *= ENEMY_ACCEL * strengthMod_;
    body_->ApplyForceToCenter(destination, true);
}

void DamagingEntity::Die()
{
    GameManager::GetInstance()->IncreaseScore(value_);
    auto ptr =  std::make_unique<AudiovisualEffect>(SpritePath::Explosion, body_->GetPosition(),
        AudioPath::Explosion, gameRef_.getWindow());
    gameRef_.GetEffects()->emplace_back(std::move(ptr));
}