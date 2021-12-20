#include "Entity.h"

#include "SFML_utilities.h"
#include "game.h"
#include "Texture_manager.h"

Entity::Entity(CollisionTag tag, Game& gameRef) : gameRef_(gameRef)
{
    userData_.SetCollisionTag(tag);
}


Entity::~Entity()
{
    Die();
	body_->GetWorld()->DestroyBody(body_);
}

void Entity::Init(float x, float y, const SpritePath& spritePath)
{
    sf::Texture& text = Texture_manager::Get_instance()->Request_texture(spritePath);

    //Define sf texture
    setTexture(text);
    setOrigin(text.getSize().x * 0.5f, text.getSize().y * 0.5f);

    // Defining the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 windowSize = pixelsToMeters(gameRef_.getWindow().getSize());
    bodyDef.position.Set(x, y);
    bodyDef.angularDamping = 0.75f;
    bodyDef.linearDamping = 0.75f;

    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this); //The userData pointer point to this object
    body_ = gameRef_.getWorld().CreateBody(&bodyDef);

    //Create the fixture 
	DefineFixture(text.getSize());
}

void Entity::DefineFixture(const sf::Vector2u textureSize)
{
    b2PolygonShape hitBox;
    hitBox.SetAsBox(pixelsToMeters(textureSize.x) * 0.5f, pixelsToMeters(textureSize.y) * 0.5f);

    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.friction = 1.0f;
    playerFixtureDef.restitution = 0.0f;
    playerFixtureDef.density = 1.0f;

    body_->CreateFixture(&playerFixtureDef);
}


void Entity::Update()
{
	setPosition(metersToPixelsCoord(body_->GetPosition(), gameRef_.getWindow().getSize()));
    setRotation(-radToDeg(body_->GetAngle()));

    //Prevent the entities from going out of the map by making them bounce
    b2Vec2 window = pixelsToMeters(gameRef_.getWindow().getSize());
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

void Entity::Die()
{
}