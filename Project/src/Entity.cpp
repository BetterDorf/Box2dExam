#include "Entity.h"

#include "SFML_utilities.h"
#include "game.h"
#include "Texture_manager.h"

Entity::Entity(CollisionTag tag)
{
    userData_.SetCollisionTag(tag);
}


Entity::~Entity()
{
    Die();
	body_->GetWorld()->DestroyBody(body_);
}

void Entity::Init(float x, float y, const std::string& spritePath)
{
    //Get the instance
    Game* game = Game::GetInstance(); 

    sf::Texture& text = Texture_manager::Get_instance()->Request_texture(spritePath);

    //Define sf texture
    setTexture(text);
    setOrigin(text.getSize().x * 0.5f, text.getSize().y * 0.5f);

    // Defining the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 windowSize = pixelsToMeters(game->getWindow().getSize());
    bodyDef.position.Set(x, y);
    bodyDef.angularDamping = 0.75f;
    bodyDef.linearDamping = 0.75f;

    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this); //The userData pointer point to this object
    body_ = game->getWorld().CreateBody(&bodyDef);

    //Create the fixture
	DefineFixture(b2Vec2(pixelsToMeters(text.getSize().x),
        pixelsToMeters(text.getSize().y)));
}

void Entity::DefineFixture(const b2Vec2 textureSize)
{
    b2PolygonShape hitBox;
    hitBox.SetAsBox(0.5f * textureSize.x, 0.5f * textureSize.y);

    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.friction = 1.0f;
    playerFixtureDef.restitution = 0.0f;
    playerFixtureDef.density = 1.0f;

    body_->CreateFixture(&playerFixtureDef);
}


void Entity::Update()
{
	setPosition(metersToPixels(body_->GetPosition()));
    setRotation(-radToDeg(body_->GetAngle()));
}

void Entity::Die()
{
}