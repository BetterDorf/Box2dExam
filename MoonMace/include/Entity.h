#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <box2d/box2d.h>

#include "UserData.h"
#include "SpritePathes.h"

class Game;

//If given a texture, the instanc should be added to the entities vector
class Entity : public sf::Sprite
{
public:
	Entity(CollisionTag tag, Game& gameRef);
	~Entity() override;

	//Take the path of the image for the sprite as well as the box2d coordinates and optionnaly, a tag for collisions
	virtual void Init(float x, float y, const SpritePath& spritePath);
	virtual void Update();

	b2Body* GetBody() { return body_; }
	UserData* GetData() { return  &userData_; }

protected:
	Game& gameRef_;

	UserData userData_;
	b2Body* body_ = nullptr;
	virtual void DefineFixture(const sf::Vector2u textureSize);
};