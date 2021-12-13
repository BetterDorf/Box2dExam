#include "game.h"

#include <random>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "GameplayConstants.h"
#include "SFML_utilities.h"

#include "Moon.h"
#include "Rope.h"
#include "GameManager.h"

Game* Game::instance = nullptr;

Game::Game() :
	m_gravity(0.0f, 0.0f),
	m_world(m_gravity)
{
	m_world.SetContactListener(&contact_listener_);
	instance = this;
}

void Game::init() {
	m_window.create(sf::VideoMode(1280, 720), "Némoz's game??");
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60.0f);

#pragma region PlayerCreation
	//Create the player
	player = std::make_unique<Player>();
	player->Init("data/Ship.png", pixelsToMeters(m_window.getSize().x / 2.0f),
		pixelsToMeters(m_window.getSize().y / 2.0f));

	b2RevoluteJointDef jointDef;
	jointDef.bodyA = player->GetBody();

	//Create all the ropes
	for (int i = 0 ; i < CHAIN_LENGTH ; i++)
	{
		//Create and init a new rope
		std::unique_ptr<Rope> newRope = std::make_unique<Rope>();
		newRope->Init("data/Chain.png", pixelsToMeters(m_window.getSize().x / 2.0f),
			pixelsToMeters(m_window.getSize().y / 2.0f));

		//Set the new rope as the second body to attach
		jointDef.bodyB = newRope->GetBody(); 

		//Define anchors
		if (i == 0)
			jointDef.localAnchorB.Set(pixelsToMeters(newRope->getTextureRect().width) / 2.0f, 0.0f);

		//Add the chain
		m_world.CreateJoint(&jointDef);

		//Setup for next chain
		entities.emplace_back(std::move(newRope));
		jointDef.bodyA = entities.back()->GetBody();
		if (i == 0)
			jointDef.localAnchorA.Set(-pixelsToMeters(entities.back()->getTextureRect().width) / 2.0f, 0.0f);
	}

	//Add the moon
	std::unique_ptr<Moon> moon = std::make_unique<Moon>();
	moon->Init("data/Moon.png", pixelsToMeters(m_window.getSize().x / 2.0f),
		pixelsToMeters(m_window.getSize().y / 2.0f));

	jointDef.bodyB = moon->GetBody();
	jointDef.localAnchorB = b2Vec2(pixelsToMeters(moon->getTextureRect().width) / 2.0f, 0);

	m_world.CreateJoint(&jointDef);
	entities.emplace(entities.begin(), std::move(moon)); // Place the moon in the vector of entities
#pragma endregion
}

void Game::loop()
{
	sf::Clock clock;
	sf::Time collectedElapsed;

	while (m_window.isOpen())
	{
#pragma region Event processes
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			// Windows events -------------------------------------------------------------------------------
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				return;
			}
		}

		//Run the game logic if the game is ongoing
		if (!GameManager::GetInstance()->IsGameOver())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
				player->Accelerate();
			else
				player->Deccelerate();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
				player->Rotate(false);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
				player->Rotate(true);
			else
				player->DeccelRotate();

	#pragma endregion
			

	#pragma region Physical process
			// Updating the world with a delay
			static constexpr float timeStep = 1.0f / 60.0f;
			static constexpr int32 velocityIterations = 6;
			static constexpr int32 positionIterations = 2;
			m_world.Step(timeStep, velocityIterations, positionIterations);

			//update all

			// Tick every 1.0sec
			sf::Time elapsed = clock.restart();
			collectedElapsed += elapsed;

	#pragma endregion

	#pragma region Update GameManager
			GameManager::GetInstance()->Update(elapsed);
	#pragma endregion
		}

#pragma region Graphics process
		// Clear all background
		m_window.clear();

		//Draw all elements
		for (auto& ent : entities)
		{
			(*ent).Update();
			m_window.draw(*ent);
		}
		player->Update();
		m_window.draw(*player);

		// Display all elements
		m_window.display();
#pragma endregion
	}
}