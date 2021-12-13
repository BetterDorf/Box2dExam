#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <box2d/b2_world.h>

#include "Entity.h"
#include "Player.h"
#include "MyContactListener.h"

class Game { //Singleton
protected:
	static Game* instance;

private:
	// The window ---------------------------------------------
	sf::RenderWindow m_window;

	std::vector<std::unique_ptr<Entity>> entities;
	std::unique_ptr<Player> player;

	// The physical world -------------------------------------
	b2Vec2 m_gravity;
	b2World m_world;
	MyContactListener contact_listener_;

public:
	//No need to check or set the instance, it is guaranteed to be set in the constructor beforehand
	static Game* GetInstance() { return instance; }
	std::vector<std::unique_ptr<Entity>>* GetEntities() { return &entities; }

	Game();
	void init();
	void loop();

	b2World& getWorld() { return m_world; }
	sf::RenderWindow& getWindow() { return  m_window; }
};