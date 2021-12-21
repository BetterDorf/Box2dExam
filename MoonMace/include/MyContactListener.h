#pragma once

#include <box2d/box2d.h>
#include <SFML/Audio/Sound.hpp>

class MyContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;

private:
	sf::Sound collisionSound;
};