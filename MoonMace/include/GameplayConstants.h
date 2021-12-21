#pragma once

//Define some variables that are only used for gamebalance and such

//Player vars

constexpr int CHAIN_LENGTH = 9;
constexpr float MAX_SPEED = 5.0f;
constexpr double MAX_ROT_SPEED = 1.0;
constexpr double ROT_SPEED = 0.006;

//Enemy vars

//Prevent enemies from spawning too close (squared)
constexpr float NOSPAWN_RADIUS = 3.0f;
constexpr int MAX_SPAWN_BUDGET = 7;
constexpr int WAVE_TO_BUDGET_INCREASE = 5;

//Amount of times we have base spawn time to rest between chunks of waves
constexpr int RESPITE_MULT = 3;

//Timers
constexpr float START_TIMER = 1.0f;
constexpr float BASE_SPAWN_TIME = 3.5f;
constexpr float TIMER_SPEED_UP = 1.1f;

constexpr int ROCKET_ODDS = 2;
constexpr int SHIP_ODDS = 13;
constexpr int BIG_STAR_ODDS = 4;
constexpr int CAPSULE_ODDS = 3;

//Budget cost
constexpr int SHIP_COST = 1;
constexpr int ROCKET_COST = 3;
constexpr int BIG_STAR_COST = 2;
constexpr int CAPSULE_COST = 1;

//Modify how much time is added until next wave
constexpr float SHIP_MOD = 0.5f;
constexpr float ROCKET_MOD = 1.5f;
constexpr float BIG_STAR_MOD = 0.9f;
constexpr float CAPSULE_MOD = 0.2f;

//Force when enemy is made
constexpr float ENEMY_IMPULSE = 5.0f;
constexpr float ENEMY_ACCEL = 0.05f;

constexpr float ROCKET_STRENGTH = 13.0f;
constexpr float BIG_STAR_STRENGTH = 3.0f;
constexpr float CAPSULE_STRENGTH = 0.4f;

constexpr int ROCKET_VALUE = 5;
constexpr int BIG_STAR_VALUE = 3;