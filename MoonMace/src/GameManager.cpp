#include "GameManager.h"

#include "SFML_Utilities.h"
#include "DamagingEntity.h"
#include "Game.h"

#include <algorithm>
#include <random>

GameManager* GameManager::instance_ = nullptr;

void GameManager::Update(sf::Time time)
{
	//update the timer
	timer_ -= time.asSeconds();

	//Spawn things accordingly
	if (timer_ <= 0)
	{
		GenericSpawn();
	}

	//Check if anything died
	if (!deadIds_.empty())
	{
		const auto entities = gameRef_.GetEntities();

		//Move all entities that died to the end of the vector
		auto it = std::remove_if(entities->begin(), entities->end(),
		[&](const std::unique_ptr<Entity>& entity)
			{
				for (const auto& id : deadIds_)
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

		deadIds_.clear();
	}
}

void GameManager::GenericSpawn()
{
	//Don't spawn anything if the game has ended
	if (gameOver_)
		return;

	//Randomly decide a "budget" for the wave
	int budget = rand() % MAX_SPAWN_BUDGET + 1;

	for (int i = 0; i < budget ; i++)
		SpawnEnemyShip();
}

void GameManager::SpawnEnemyShip()
{
	b2Vec2 pos = GenerateSpawnPosition();

	score_++;
	
	std::unique_ptr<DamagingEntity> uPtr = std::make_unique<DamagingEntity>(gameRef_, curId_++);
	uPtr->Init(pos.x, pos.y, SpritePath::StarEnemy);

	gameRef_.GetEntities()->emplace_back(std::move(uPtr));

	//Handle timer modifs
	timer_ += timeBetweenSpawn_ * shipMod_;
	timeBetweenSpawn_ /= spawnIncrease_;
}


bool GameManager::IsGameOver() const
{
	return gameOver_;
}

void GameManager::GameOver()
{
	gameOver_ = true;
}

int GameManager::GetScore() const
{
	return score_;
}

void GameManager::AddDeadId(int id)
{
	score_++;

	deadIds_.emplace_back(id);
}

b2Vec2 GameManager::GenerateSpawnPosition()
{
	b2Vec2 pos;

	int maxY = gameRef_.getWindow().getSize().y;
	int maxX = gameRef_.getWindow().getSize().x;

	do
	{
		pos = b2Vec2(pixelsToMeters(sf::Vector2f(static_cast<float>(rand() % maxX), static_cast<float>(rand() % maxY))));
	} while ((gameRef_.GetPlayerPos() - pos).Length() < NOSPAWN_RADIUS);

	return pos;
}

void GameManager::Reset()
{
	gameOver_ = false;
	score_ = 0;
	timeBetweenSpawn_= BASE_SPAWN_TIME;
	timer_ = START_TIMER;
}
