#include "GameManager.h"

#include "game.h"
#include "SFML_Utilities.h"
#include "DamagingEntity.h"

#include <algorithm>
#include <random>

GameManager* GameManager::instance = nullptr;

void GameManager::Update(sf::Time time)
{
	//update the timer
	timer -= time.asSeconds();

	//Spawn things accordingly
	if (timer <= 0)
	{
		GenericSpawn();
	}

	//Check if anything died
	if (!deadIds.empty())
	{
		const auto entities = Game::GetInstance()->GetEntities();

		//Move all entities that died to the end of the vector
		auto it = std::remove_if(entities->begin(), entities->end(),
		[&](const std::unique_ptr<Entity>& entity)
			{ for (const auto& id : deadIds) { if (entity->GetId() == id) return true; } return false; });
		 
		//Kill and free the memory for each dead entity found
		std::for_each(it, entities->end(),
			[](std::unique_ptr<Entity>& entity) { entity.release(); });

		//Clean them from the game's vector of entities
		entities->erase(it, entities->end());

		deadIds.clear();
	}
}

void GameManager::GenericSpawn()
{
	//Don't spawn anything if the game has ended
	if (gameOver)
		return;

	//For now, only spawn enemy ships
	SpawnEnemyShip(1);
	timer = timeBetweenSpawn * shipMod;
	timeBetweenSpawn /= spawnIncrease;
}

void GameManager::SpawnEnemyShip(const int& num)
{
	score++;

	Game* game = Game::GetInstance();

	int maxX = game->getWindow().getSize().x;
	int maxY = game->getWindow().getSize().y;

	int posX = rand() % maxX;
	int posY = rand() % maxY;

	for (int i = 0 ; i < num ; i++)
	{
		std::unique_ptr<DamagingEntity> uPtr = std::make_unique<DamagingEntity>(curId++);
		uPtr->Init("data/StarShip.png", pixelsToMeters(posX), pixelsToMeters(posY), Tag::DAMAGING);

		game->GetEntities()->emplace_back(std::move(uPtr));
	}
}


bool GameManager::IsGameOver() const
{
	return gameOver;
}

void GameManager::GameOver()
{
	gameOver = true;
}

int GameManager::GetScore() const
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

void GameManager::AddDeadId(int id)
{
	score++;

	deadIds.emplace_back(id);
}