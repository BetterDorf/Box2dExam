
#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Ball
{
public:
	explicit Ball(Game& game_, sf::RenderWindow& window_);

	void init();
	void update();
	void render();
	void setPixelsPosition(sf::Vector2f _pixelsPosition);

private:
	Game& game;

	sf::CircleShape shape;
	sf::RenderWindow& window;
	b2Body* body = nullptr;

};
