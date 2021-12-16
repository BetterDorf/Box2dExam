#pragma once
#include <SFML/Window.hpp>
#include <box2d/b2_math.h>
#include "GameplayConstants.h"

//Game manager manages everything that happens game-wise :
// It handles Spawning, scoring
// It doesn't handle physics or collisions.
class GameManager //Singleton
{
	//Decide and call the other spawn functions then reset the timer
	void GenericSpawn(); 
	void SpawnEnemyShip();

	b2Vec2 GenerateSpawnPosition();

	bool gameOver = false;

	//1 is gained per thing created and 1 more per destroyed
	int score = 0;

	//The id things get created with, goes up after each creation
	int curId = 1;

	//The ids of the things that need to be destroyed
	std::vector<int> deadIds;

	//The timer is set to time between spawn multiplied by the spawnee's mod
	float timeBetweenSpawn = BASE_SPAWN_TIME;
	float shipMod = 0.5f;
	float timer = START_TIMER;
	float spawnIncrease = 1.01f;

	static GameManager* instance;
public:
	static GameManager* GetInstance();

	//Take elapsed time and call spawn methods
	void Update(sf::Time time);

	//Check if the game has ended
	bool IsGameOver() const;
	void GameOver();
	void Reset();
	
	int GetScore() const;

	void AddDeadId(int id);
};