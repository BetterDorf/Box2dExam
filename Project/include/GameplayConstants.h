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
//Force when enemy is made
constexpr float ENEMY_IMPULSE = 5.0f;
constexpr float ENEMY_ACCEL = 0.05f;