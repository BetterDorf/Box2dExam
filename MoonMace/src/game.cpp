#include "Game.h"

#include <iomanip>
#include <random>
#include <time.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <sstream>
#include <string>

#include "GameplayConstants.h"
#include "ProgramConstants.h"
#include "SFML_utilities.h"

#include "Moon.h"
#include "Rope.h"

Game::Game() : m_gravity(0.0f, 0.0f), m_world(m_gravity), gameManager_(*this)
{
	m_world.SetContactListener(&contact_listener_);
	srand(time(NULL));
}

void Game::SetupTexts()
{
	//font
	m_font.loadFromFile("data/Fonts/upheavtt.ttf");

	//Score
	m_score_text.setString("0");
	m_score_text.setFont(m_font);
	m_score_text.setFillColor(sf::Color::White);
	m_score_text.setCharacterSize(75);
	m_score_text.setOrigin(m_score_text.getGlobalBounds().width / 2.0f,
		m_score_text.getGlobalBounds().height / 2.0f);
	m_score_text.setPosition(m_window.getSize().x / 20.0f, m_window.getSize().y / 20.0f);

	//GameOver
	m_game_over_text.setString("GAME OVER");
	m_game_over_text.setFont(m_font);
	m_game_over_text.setFillColor(sf::Color::White);
	m_game_over_text.setCharacterSize(200);
	m_game_over_text.setStyle(sf::Text::Bold);
	m_game_over_text.setOrigin(m_game_over_text.getGlobalBounds().width / 2.0f,
		m_game_over_text.getGlobalBounds().height / 2.0f);
	m_game_over_text.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f);

	//Wave
	m_wave_text.setString("Wave : 0");
	m_wave_text.setFont(m_font);
	m_wave_text.setFillColor(sf::Color::Yellow);
	m_wave_text.setCharacterSize(30);
	m_wave_text.setOrigin(m_wave_text.getGlobalBounds().width,
		m_wave_text.getGlobalBounds().height / 2.0f);
	m_wave_text.setPosition(m_window.getSize().x - m_window.getSize().x / 20.0f, m_window.getSize().y / 20.0f);

	m_wave_time_text.setString("0.0");
	m_wave_time_text.setFont(m_font);
	m_wave_time_text.setFillColor(sf::Color::Green);
	m_wave_time_text.setCharacterSize(25);
	m_wave_time_text.setPosition(m_wave_time_text.getGlobalBounds().width,
		m_window.getSize().y - m_wave_time_text.getGlobalBounds().height * 3);
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

	SetupTexts();

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


void Game::defineMenu()
{
	//Define all that needs to be written
	sf::Text text;
	text.setString("MoonMace");
	text.setFont(m_font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(200);
	text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
	text.setPosition(m_window.getSize().x / 2.0f, 100);
	texts_.emplace_back(std::make_unique<sf::Text>(text));

	text.setString("Controls:");
	text.setCharacterSize(100);
	text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
	text.setPosition(m_window.getSize().x / 2.0f, 300);
	texts_.emplace_back(std::make_unique<sf::Text>(text));

	text.setString("Space: Pause/Play");
	text.setCharacterSize(50);
	text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
	text.setPosition(m_window.getSize().x / 2.0f, 400);
	texts_.emplace_back(std::make_unique<sf::Text>(text));

	text.setString("Esc: Exit");
	text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
	text.setPosition(m_window.getSize().x / 2.0f, 450);
	texts_.emplace_back(std::make_unique<sf::Text>(text));

	text.setString("W: Go forward");
	text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
	text.setPosition(m_window.getSize().x / 2.0f, 500);
	texts_.emplace_back(std::make_unique<sf::Text>(text));

	text.setString("A/D: Turn");
	text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
	text.setPosition(m_window.getSize().x / 2.0f, 550);
	texts_.emplace_back(std::make_unique<sf::Text>(text));

	text.setString("Music : https://arcofdream.bandcamp.com/track/shelf-space \n"
		"Code : Shamelessly copied from all over internet\n"
		"Things that barely work : me");
	text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
	text.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y - text.getGlobalBounds().height);
	texts_.emplace_back(std::make_unique<sf::Text>(text));
}


bool Game::loop()
{
	sf::Clock clock;
	sf::Time collectedElapsed;

	while (m_window.isOpen())
	{
		//Register the time that has passed
		sf::Time elapsed = clock.restart();
		collectedElapsed += elapsed;

#pragma region Event processes
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			// Windows events -------------------------------------------------------------------------------
			if (event.type == sf::Event::Closed)
			{
				//Clear the entities
				CloseGame();
				return false;
			}

			//Handle space press here to have only the key down event
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					if(gameManager_.IsGameOver())
					{
						//Clear up last game
						entities.clear();
						effects.clear();
						player.reset();

						//Startup new one
						this->init();
						return true;
					}

					gamePaused = !gamePaused;
				}
			}
		}


#pragma endregion
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			//Clear the entities
			CloseGame();
			return false;
		}

		//Show the menu
		if(gamePaused)
		{
			m_window.clear();

			for (auto& text : texts_)
			{
				m_window.draw(*text.get());
			}

			m_window.display();

			continue;
		}


		//Run the movement logic only if the game isn't over
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

#pragma region Physical process
			// Updating the world with a delay
			static constexpr float timeStep = 1.0f / 60.0f;
			static constexpr int32 velocityIterations = 6;
			static constexpr int32 positionIterations = 2;
			m_world.Step(timeStep, velocityIterations, positionIterations);
#pragma endregion

#pragma region Update GameManager
			GameManager::GetInstance()->Update(elapsed);
#pragma endregion

#pragma region Graphics process
		// Clear all background
		m_window.clear();

		//Animate and cleanup visual effects every 5 frames
		if (IncrementFrameCounter() == 0)
		{
			if (!effects.empty())
			{
				auto it = std::remove_if(effects.begin(), effects.end(),
					[&](const std::unique_ptr<AudiovisualEffect>& entity) {return !entity->Animate(); });
				effects.erase(it, effects.end());
			}
		}
		//Draw the effects
		for (auto& ent : effects)
		{
			m_window.draw(*ent);
		}

		//Draw normal elements
		for (auto& ent : entities)
		{
			(*ent).Update();
			m_window.draw(*ent);
		}
		player->Update();
		m_window.draw(*player);

#pragma region UI
		m_wave_text.setString("Wave : " + std::to_string(gameManager_.GetWave()));
		m_window.draw(m_wave_text);
		if (GameManager::GetInstance()->IsGameOver())
		{
			m_window.draw(m_game_over_text);
		}
		else
		{
			std::ostringstream oss;
			oss << std::setprecision(2) << gameManager_.GetTimer();
			m_wave_time_text.setString(oss.str());
			m_window.draw(m_wave_time_text);
			m_score_text.setString(std::to_string(gameManager_.GetScore()));
			m_window.draw(m_score_text);
		}
#pragma endregion

		// Display all elements
		m_window.display();
#pragma endregion
	}
}

void Game::CloseGame()
{
	effects.clear();
	entities.clear();
	player.release();

	m_window.close();
}

int Game::IncrementFrameCounter()
{
	frameCounter++;
	frameCounter %= FRAMES_PER_ANIMATION_STEP;
	return frameCounter;
}

void Game::AnnouncerSay(AudioPath path)
{
	announcer.setBuffer(audioManager_.RequestBuffer(path));
	announcer.play();
}

void Game::GameOverChanges()
{
	m_game_over_text.setString(m_game_over_text.getString() + "\nScore : " + m_score_text.getString());
}