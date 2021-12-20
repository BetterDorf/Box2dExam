#include "Game.h"

#include <random>
#include <time.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <string>

#include "GameplayConstants.h"
#include "SFML_utilities.h"

#include "Moon.h"
#include "Rope.h"

bool Game::gameStarted = false;

Game::Game() : m_gravity(0.0f, 0.0f), m_world(m_gravity), gameManager_(*this)
{
	m_world.SetContactListener(&contact_listener_);
	srand(time(NULL));
}

void Game::init()
{
	if(!gameStarted)
	{
		gameStarted = true;

		m_window.create(sf::VideoMode::getFullscreenModes()[0], "Moon Mace", sf::Style::Fullscreen);
		m_window.setMouseCursorVisible(false);
		m_window.setVerticalSyncEnabled(true);
		m_window.setFramerateLimit(60.0f);

		audioManager_.PlayMusic();
	}
	else
	{
		GameManager::GetInstance()->Reset();
	}

#pragma region UI
	//font
	m_font.loadFromFile("data/Fonts/upheavtt.ttf");

	//Score
	m_score_text.setString("0");
	m_score_text.setFont(m_font);
	m_score_text.setFillColor(sf::Color::White);
	m_score_text.setCharacterSize(50);
	m_score_text.setPosition(50, 50);
	 
	//GameOver
	m_game_over_text.setString("GAME OVER");
	m_game_over_text.setFont(m_font);
	m_game_over_text.setFillColor(sf::Color::White);
	m_game_over_text.setCharacterSize(200);
	m_game_over_text.setStyle(sf::Text::Bold);
	m_game_over_text.setPosition(m_window.getSize().x / 10.0f, m_window.getSize().y / 2.0f);
#pragma endregion

#pragma region PlayerCreation
	//Create the player
	player = std::make_unique<Player>(*this);
	player->Init(pixelsToMeters(m_window.getSize().x / 2.0f),
		pixelsToMeters(m_window.getSize().y / 2.0f));

	//Define the joint used by all of rope link
	b2RevoluteJointDef jointDef;

	//Create all the ropes
	jointDef.bodyA = player->GetBody();
	for (int i = 0 ; i < CHAIN_LENGTH ; i++)
	{
		//Create and init a new rope
		std::unique_ptr<Rope> newRope = std::make_unique<Rope>(*this);
		newRope->Init(pixelsToMeters(m_window.getSize().x / 2.0f),
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
	std::unique_ptr<Moon> moon = std::make_unique<Moon>(*this);
	moon->Init(pixelsToMeters(m_window.getSize().x / 2.0f),
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
				//Clear the entities
				CloseGame();
				return;
			}
		}


#pragma endregion
		//Run the movement logic if the game is ongoing
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
		}
		else
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				//Clear the entities
				CloseGame();
				return;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			{
				//Clear up last game
				entities.clear();
				player.reset();

				//Startup new one
				this->init();
				this->loop();
				return;
			}
		}

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

#pragma region UI
		m_score_text.setString(std::to_string(GameManager::GetInstance()->GetScore()));
		m_window.draw(m_score_text);

		if (GameManager::GetInstance()->IsGameOver())
		{
			m_window.draw(m_game_over_text);
		}
#pragma endregion

		// Display all elements
		m_window.display();
#pragma endregion
	}
}

void Game::CloseGame()
{
	entities.clear();
	player.release();

	m_window.close();
}