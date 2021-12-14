#pragma once

#include <vector>
#include "raylib.h"
#include "ui.hpp"

// Forwards declarations.
class Entity;
class Enemy;
class Tower;


enum class GameDifficulty : int
{
    EASY,
    MEDIUM,
    HARD
};

// Game class.
class Game
{
public:

    bool needStop = false;

    // Attributes.
    TileMapEditor mTm;
    
    // Constructor.
    Game();

    // Gamemode related methods.
    void LoadRound();
    void InitRound();
    void RoundUpdate();

    // Core related methods.
    void UpdateGame(Ui &ui);
    void DrawGame();
    void UnloadData();

private:
    // Members.
    bool  mIsRunning;
    bool  mUpdatingEntities;
    bool  mSpawnTower;
    int   mMoney;
    float mDeltaTime;
};