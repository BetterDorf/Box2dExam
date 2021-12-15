#include "Entity.h"

#include "SFML_utilities.h"
#include "game.h"
#include "Texture_manager.h"

Entity::~Entity()
{
    Die();
	body_->GetWorld()->DestroyBody(body_);
}

void Entity::Init(const std::string& spritePath, float x, float y, Tag tag)
{
    //Get the instances
    sf::Texture& text = Texture_manager::Get_instance()->Request_texture(spritePath);
    Game* game = Game::GetInstance();

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

    //Change the user data
    userData_.SetTag(tag);
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

    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);

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