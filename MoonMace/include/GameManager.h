#pragma once
#include <SFML/Window.hpp>
#include <box2d/b2_math.h>

#include "GameplayConstants.h"

class Game;

//Game manager manages everything that happens game-wise :
// It handles Spawning, scoring
// It doesn't handle physics or collisions.
class GameManager
{
public:
	GameManager(Game& gameRef) : gameRef_(gameRef) { instance_ = this; }

	static GameManager* GetInstance() { return instance_; }

	//Take elapsed time and call spawn methods
	void Update(sf::Time time);

	//Check if the game has ended
	bool IsGameOver() const;
	void GameOver();
	void Reset();
	
	int GetScore() const;
	int GetWave() const;
	float GetTimer() const;

	void IncreaseScore(int value);

	void AddDeadId(int id);

protected:
	static GameManager* instance_;

private:
	Game& gameRef_;

	//Decide and call the other spawn functions then reset the timer
	void GenericSpawn(); 
	void SpawnEnemyShip();
	void SpawnRocket();
	void SpawnBigStar();
	void SpawnCapsule();

	b2Vec2 GenerateSpawnPosition();

	bool gameOver_ = false;

	//1 is gained per thing created and 1 more per destroyed
	int score_ = 0;
	int wave_ = 0;

	//The id things get created with, goes up after each creation
	int curId_ = 1;

	//The ids of the things that need to be destroyed
	std::vector<int> deadIds_;

	//The timer is set to time between spawn multiplied by the spawnee's mod
	float timeBetweenSpawn_ = BASE_SPAWN_TIME;
	float timer_ = START_TIMER;
};