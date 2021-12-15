#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <box2d/box2d.h>

#include "UserData.h"

class Game;

class Entity : public sf::Sprite
{
protected:
	UserData userData_;
	b2Body* body_ = nullptr;
	virtual void DefineFixture(const b2Vec2 textureSize);
	int id_ = 0;

	virtual void Die();
public:
	Entity() = default;
	~Entity();

	//Take the path of the image for the sprite as well as the box2d coordinates and optionnaly, a tag for collisions
	virtual void Init(const std::string& spritePath, float x, float y, Tag tag = Tag::DEFAULT);
	void Update();

	b2Body* GetBody() { return body_; }
	UserData* GetData() { return  &userData_; }
	int GetId() { return id_; }
};