#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "box2d/b2_world.h"

#include "ball.h"

class Game{
public:
	Game();
	void init();
	void loop();

	b2World& getWorld() { return world_; };

	static b2Vec2 pixelsToMeters(sf::Vector2f pixels);
	static b2Vec2 pixelsToMeters(sf::Vector2u pixels);
	static float pixelsToMeters(float pixels);

	static sf::Vector2f metersToPixels(b2Vec2 meters);

	static const float pixelsMetersRatio;

private:
	// The window ---------------------------------------------
	sf::RenderWindow window_;

	sf::Font font_;

	// The physical world -------------------------------------
	b2World world_{ b2Vec2(0.0f, -9.81f) };

	Ball theBall;

};
