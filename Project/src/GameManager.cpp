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
			{
				for (const auto& id : deadIds)
				{
					if(auto damaging = static_cast<DamagingEntity*>(entity.get()))
					if (damaging->GetId() == id) 
						return true;
				}
				return false;
			});

		//Erase them from the game's vector of entities
		//Since those are smart pointers, when they are erased they will delete the entity
		entities->erase(it, entities->end());

		deadIds.clear();
	}
}

void GameManager::GenericSpawn()
{
	//Don't spawn anything if the game has ended
	if (gameOver)
		return;

	//Randomly decide a "budget" for the wave
	int budget = rand() % MAX_SPAWN_BUDGET + 1;

	for (int i = 0; i < budget ; i++)
		SpawnEnemyShip();
}

void GameManager::SpawnEnemyShip()
{
	b2Vec2 pos = GenerateSpawnPosition();

	score++;
	
	std::unique_ptr<DamagingEntity> uPtr = std::make_unique<DamagingEntity>(curId++);
	uPtr->Init(pos.x, pos.y, "data/StarShip.png");

	Game::GetInstance()->GetEntities()->emplace_back(std::move(uPtr));

	//Handle timer modifs
	timer += timeBetweenSpawn * shipMod;
	timeBetweenSpawn /= spawnIncrease;
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

b2Vec2 GameManager::GenerateSpawnPosition()
{
	Game* game = Game::GetInstance();
	b2Vec2 pos;

	int maxY = game->getWindow().getSize().y;
	int maxX = game->getWindow().getSize().x;

	do
	{
		pos = b2Vec2(pixelsToMeters(sf::Vector2f(static_cast<float>(rand() % maxX), static_cast<float>(rand() % maxY))));
	} while ((Game::GetInstance()->GetPlayerPos() - pos).Length() < NOSPAWN_RADIUS);

	return pos;
}

void GameManager::Reset()
{
	gameOver = false;
	score = 0;
	timeBetweenSpawn = BASE_SPAWN_TIME;
	timer = START_TIMER;
}
