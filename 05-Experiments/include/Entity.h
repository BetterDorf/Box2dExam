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

public:
	Entity() {}
	void Init(const std::string& spritePath, float x, float y);
	void Update();

	b2Body* GetBody() { return body_; }
	UserData* GetData() { return  &userData_; }
};