#pragma once
#include <SFML/Window.hpp>

//Game manager manages everything that happens game-wise :
// It handles Spawning, scoring
// It doesn't handle physics or collisions.

class GameManager //Singleton
{
	//Decide and call the other spawn functions then reset the timer
	void GenericSpawn(); 
	void SpawnEnemyShip(const int& num);


	int score = 0;

	//The timer is set to time between spawn multiplied by the spawnee's mod
	float timeBetweenSpawn = 5.0f;
	float shipMod = 1.0f;
	float timer = 10.0f;

	static GameManager* instance;
public:
	static GameManager* GetInstance();

	//Take elapsed time and call spawn methods
	void Update(sf::Time time);

	//Check if the game has ended
	bool IsGameOver();
	
	int GetScore();
};