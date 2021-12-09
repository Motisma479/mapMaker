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


// Player class.
class Player
{
public:
    // Attributes.
    

    bool           isDragging;
    int            money;
    int            hp;
    vector<Tower*> towers;

    // Constructor / destructor.
    Player();
    ~Player();

    // Action methods.
    void Purchase(Tower tower);
    void Sell(Tower tower); //1/3 origin price.wer
    
    // Display methods.
    void BuildMode(Tower tower); //TODO 

    // Main methods.
    void Init();
    void Update();
};

// Game class.
class Game
{
public:

    bool needStop = false;

    // Attributes.
    static GameDifficulty difficulty;
    Player                player;
    TileMap               tm;

    std::vector<class Entity*> mEntities;
    std::vector<class Entity*> mPendingEntities;
    std::vector<class Enemy*>  mEnemies;
    
    // Constructor.
    Game();

    // Entities related methods.
    void AddEntity(class Entity* entity);
    void RemoveEntity(class Entity* entity);
    void UpdateEntities();

    // Enemies related methods.
    void AddEnemy(class Enemy* enemy);
    void RemoveEnemy(class Enemy* enemy);
    std::vector<class Enemy*>&  GetEnemies();
    std::vector<class Entity*>& GetEntities();
    Enemy* GetNearestEnemy(const Vector2& pos);

    // Gamemode related methods.
    void LoadRound();
    void InitRound();
    void RoundUpdate();

    // Core related methods.
    void LoadData();
    void UpdateGame(Ui &ui);
    void DrawGame();
    void UnloadData();

private:
    // Members.
    bool            mIsRunning;
    bool            mUpdatingEntities;
    bool            mSpawnTower;
    int             mMoney;
    float           mDeltaTime;

};