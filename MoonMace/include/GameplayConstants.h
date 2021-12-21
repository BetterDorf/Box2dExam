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
constexpr int MAX_SPAWN_BUDGET = 8;

constexpr int ROCKET_ODDS = 2;
constexpr int SHIP_ODDS = 13;
constexpr int BIG_STAR_ODDS = 4;

constexpr int SHIP_COST = 1;
constexpr int ROCKET_COST = 3;
constexpr int BIG_STAR_COST = 2;

constexpr float START_TIMER = 1.0f;
constexpr float BASE_SPAWN_TIME = 5.0f;
constexpr float TIMER_SPEED_UP = 1.015f;

constexpr float SHIP_MOD = 0.5f;
constexpr float ROCKET_MOD = 1.5f;
constexpr float BIG_STAR_MOD = 0.9f;

//Force when enemy is made
constexpr float ENEMY_IMPULSE = 5.0f;
constexpr float ENEMY_ACCEL = 0.05f;

constexpr float ROCKET_STRENGTH = 13.0f;
constexpr float BIG_STAR_STRENGTH = 3.0f;

constexpr int ROCKET_VALUE = 5;
constexpr int BIG_STAR_VALUE = 3;