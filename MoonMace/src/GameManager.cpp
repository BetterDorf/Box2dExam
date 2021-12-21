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
					{
						damaging->Die();
						return true;
					}
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

	//Increase the wave count and reset the acceleration of waves
	wave_++;
	if (wave_ % WAVE_TO_BUDGET_INCREASE == 0)
	{
		timeBetweenSpawn_ = BASE_SPAWN_TIME;

		//Give respite time
		timer_ = BASE_SPAWN_TIME * RESPITE_MULT;
	}

	//Randomly decide a "budget" for the wave
	//1 additional max budget per x waves
	//min budget is half of max budget
	int minBudget = (MAX_SPAWN_BUDGET + wave_ / WAVE_TO_BUDGET_INCREASE) / 2;
	int budget = rand() % (MAX_SPAWN_BUDGET + wave_ / WAVE_TO_BUDGET_INCREASE - minBudget + 1) + minBudget;

	do
	{
		//Choose a random number between 0 and the total of all weights
		int num = rand() % (ROCKET_ODDS + SHIP_ODDS + BIG_STAR_ODDS + CAPSULE_ODDS); 

		num -= SHIP_ODDS;
		if (num < 0)
		{
			if (budget < SHIP_COST)
				break;
			SpawnEnemyShip();
			budget -= SHIP_COST;
			continue;
		}

		num -= ROCKET_ODDS;
		if (num < 0)
		{
			if (budget < ROCKET_COST)
				break;
			SpawnRocket();
			budget -= ROCKET_COST;
			continue;
		}

		num -= BIG_STAR_ODDS;
		if (num < 0)
		{
			if (budget < BIG_STAR_COST)
				break;
			SpawnBigStar();
			budget -= BIG_STAR_COST;
			continue;
		}

		num -= CAPSULE_ODDS;
		if (num < 0)
		{
			if (budget < CAPSULE_COST)
				break;
			SpawnCapsule();
			budget -= CAPSULE_COST;
			continue;
		}

		break;
		
	} while (budget > 0);
}

void GameManager::SpawnEnemyShip()
{
	b2Vec2 pos = GenerateSpawnPosition();
	
	std::unique_ptr<DamagingEntity> uPtr = std::make_unique<DamagingEntity>(gameRef_, curId_++, 1.0f, 1);
	uPtr->Init(pos.x, pos.y, SpritePath::StarEnemy);

	gameRef_.GetEntities()->emplace_back(std::move(uPtr));

	//Handle timer modifs
	timer_ += timeBetweenSpawn_ * SHIP_MOD;
	timeBetweenSpawn_ /= TIMER_SPEED_UP;
}

void GameManager::SpawnRocket()
{
	b2Vec2 pos = GenerateSpawnPosition();

	std::unique_ptr<DamagingEntity> uPtr = std::make_unique<DamagingEntity>(gameRef_, curId_++, ROCKET_STRENGTH, ROCKET_VALUE);
	uPtr->Init(pos.x, pos.y, SpritePath::Rocket);

	gameRef_.GetEntities()->emplace_back(std::move(uPtr));

	//Handle timer modifs
	timer_ += timeBetweenSpawn_ * ROCKET_MOD;
	timeBetweenSpawn_ /= TIMER_SPEED_UP;
}


void GameManager::SpawnBigStar()
{
	b2Vec2 pos = GenerateSpawnPosition();

	std::unique_ptr<DamagingEntity> uPtr = std::make_unique<DamagingEntity>(gameRef_, curId_++,
		BIG_STAR_STRENGTH, BIG_STAR_VALUE);
	uPtr->Init(pos.x, pos.y, SpritePath::StarEnemy2);

	gameRef_.GetEntities()->emplace_back(std::move(uPtr));

	//Handle timer modifs
	timer_ += timeBetweenSpawn_ * BIG_STAR_MOD;
	timeBetweenSpawn_ /= TIMER_SPEED_UP;
}

void GameManager::SpawnCapsule()
{
	b2Vec2 pos = GenerateSpawnPosition();

	std::unique_ptr<DamagingEntity> uPtr = std::make_unique<DamagingEntity>(gameRef_, curId_++, CAPSULE_STRENGTH, 1);
	uPtr->Init(pos.x, pos.y, SpritePath::Capsule);

	gameRef_.GetEntities()->emplace_back(std::move(uPtr));

	//Handle timer modifs
	timer_ += timeBetweenSpawn_ * CAPSULE_MOD;
	timeBetweenSpawn_ /= TIMER_SPEED_UP;
}

bool GameManager::IsGameOver() const
{
	return gameOver_;
}

void GameManager::GameOver()
{
	gameOver_ = true;

	//Play an appropriate gameOver sound
	AudioPath relevantMessage = AudioPath::GameOver1;
	while (rand() % 2 != 0)
	{
		if (relevantMessage == AudioPath::GameOver1)
			relevantMessage = AudioPath::GameOver2;
		else if (relevantMessage == AudioPath::GameOver2)
			relevantMessage = AudioPath::GameOver3;
		else if (relevantMessage == AudioPath::GameOver3)
			relevantMessage = AudioPath::GameOver4;
		else
			break;
	}

	gameRef_.GameOverChanges();
	gameRef_.AnnouncerSay(relevantMessage);
}

int GameManager::GetScore() const
{
	return score_;
}

int GameManager::GetWave() const
{
	return wave_;
}

float GameManager::GetTimer() const
{
	return timer_;
}



void GameManager::IncreaseScore(int value)
{
	if (!gameOver_)
		score_ += value;
}

void GameManager::AddDeadId(int id)
{
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
	wave_ = 0;
	timeBetweenSpawn_= BASE_SPAWN_TIME;
	timer_ = START_TIMER;
}