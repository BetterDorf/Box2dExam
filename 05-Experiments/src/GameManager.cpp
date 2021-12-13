#include "GameManager.h"

#include "game.h"
#include "SFML_Utilities.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Update(sf::Time time)
{
	timer -= time.asSeconds();

	if (timer <= 0)
	{
		GenericSpawn();
	}
}

void GameManager::GenericSpawn()
{
	//For now, only spawn enemy ships
	SpawnEnemyShip(1);
	timer = timeBetweenSpawn * shipMod;
}

void GameManager::SpawnEnemyShip(const int& num)
{
	Game* game = Game::GetInstance();

	int maxX = pixelsToMeters(game->getWindow().getSize().x);
	int maxY = pixelsToMeters(game->getWindow().getSize().y);

	for (int i = 0 ; i < num ; i++)
	{
		game->GetEntities()->emplace_back(std::make_unique<Entity>());
		game->GetEntities()->back()->Init("data/StarShip.png", maxX / 2.0f, maxY / 2.0f); //not random for now
	}
}


bool GameManager::IsGameOver()
{
	return false; //For now, game can't end
}


int GameManager::GetScore()
{
	return score;
}


GameManager* GameManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}

	return instance;
}