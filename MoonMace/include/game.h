#pragma once
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <box2d/b2_world.h>

#include "Entity.h"
#include "AudiovisualEffect.h"
#include "Player.h"

#include "MyContactListener.h"
#include "GameManager.h"
#include "Texture_manager.h"
#include "AudioManager.h"

class Game {
public:
	Game();

	void init();
	void defineMenu();
	//Return true each time the player wants to play again
	bool loop();

	std::vector<std::unique_ptr<Entity>>* GetEntities() { return &entities; }
	std::vector<std::unique_ptr<AudiovisualEffect>>* GetEffects() { return &effects; }

	b2Vec2 GetPlayerPos() { return player->GetBody()->GetPosition(); }

	b2World& getWorld() { return m_world; }
	sf::RenderWindow& getWindow() { return  m_window; }

	void AnnouncerSay(AudioPath path);
	void GameOverChanges();


private:
	bool gameStarted;
	bool gamePaused = true;

	//Managers
	GameManager gameManager_;
	Texture_manager textureManager_;
	AudioManager audioManager_;

	// The window ---------------------------------------------
	sf::RenderWindow m_window;

	//UI
	void SetupTexts();
	sf::Font m_font;
	sf::Text m_score_text;
	sf::Text m_game_over_text;
	sf::Text m_wave_text;
	sf::Text m_wave_time_text;
	std::vector<std::unique_ptr<sf::Text>> texts_;

	//Entities
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::unique_ptr<AudiovisualEffect>> effects;
	std::unique_ptr<Player> player;

	//Animation
	int IncrementFrameCounter();
	int frameCounter = 0;

	//Audio
	sf::Sound announcer;

	// The physical world -------------------------------------
	b2Vec2 m_gravity;
	b2World m_world;
	MyContactListener contact_listener_;

	void CloseGame();
};