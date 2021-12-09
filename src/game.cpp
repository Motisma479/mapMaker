#include <algorithm>
#include <iostream>

#include "ui.hpp"
#include "resources.hpp"

#include "game.hpp"

using namespace std;

GameDifficulty Game::difficulty = GameDifficulty::EASY;

//* PLAYER CLASS ================================
// -------------- ACTION METHODS ------------- //

Player::Player() : isDragging(false), money(0), hp(0)
{
}

Player::~Player()
{
    towers.clear();
}

// -------------- ACTION METHODS ------------- //

// void Player::Purchase(Tower tower)
// {
//     if (money >= tower.stats.cost) money -= tower.stats.cost;
// }

// void Player::Sell(Tower tower)
// {
//    money += (int)(std::floor(tower.stats.cost / 3));
// }

// -------------- DISPLAY METHODS ------------ //

// void Player::BuildMode(Tower tower)
// {
//     //TODO Draw ghosted tower texture to the mouse pos. 
//     DrawCircleV(tower.GetCircle()->GetCenter(),
//                 tower.GetCircle()->GetRadius(),
//                 {255,0,0,150});
// }

// --------------- MAIN METHODS ------------- //

void Player::Init()
{
    switch (Game::difficulty)
    {
    case GameDifficulty::EASY:
        money = 150000;
        hp    = 200;
        break;

    case GameDifficulty::MEDIUM:
        money = 75000;
        hp    = 100;
        break;

    case GameDifficulty::HARD:
        money = 50000;
        hp    = 50;
        break;
    
    default:
        break;
    }
}

//* GAME CLASS ==================================
// --------------- CONSTRUCTOR --------------- //

Game::Game()
    : mIsRunning(true)
    , mUpdatingEntities(false)
    , mSpawnTower(false)
{
}

// --------- ENTITIES RELATED METHODS -------- //

void Game::AddEntity(class Entity* entity)
{
    if (mUpdatingEntities) mEntities.emplace_back(entity);
    else                   mPendingEntities.emplace_back(entity);
}

void Game::RemoveEntity(class Entity* entity)
{
    // Clean pending entities container.
    auto iter = find(mPendingEntities.begin(), mPendingEntities.end(), entity);

    if (iter != mPendingEntities.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        iter_swap(iter,mPendingEntities.end() - 1);
        mPendingEntities.pop_back();
    }

    // Clean entities container.
    iter = find(mEntities.begin(), mEntities.end(), entity);
    if (iter != mPendingEntities.end())
    {
        iter_swap(iter,mEntities.end() - 1);
        mEntities.pop_back();
    }
}

// --------- ENEMIES RELATED METHODS --------- //

void Game::AddEnemy(class Enemy* enemy)
{
    mEnemies.emplace_back(enemy);
}

void Game::RemoveEnemy(class Enemy* enemy)
{
    auto iter = find(mEnemies.begin(), mEnemies.end(), enemy);
    mEnemies.erase(iter);
}

std::vector<class Enemy*>& Game::GetEnemies()
{
    return mEnemies;
}

std::vector<class Entity*>& Game::GetEntities()
{
    return mEntities;
}

// Enemy* Game::GetNearestEnemy(const Vector2& pos)
// {
//     Enemy* nearest = nullptr;
//     if (mEnemies.size() > 0)
//     {
//         nearest = mEnemies[0];
//         float nearestdistX  = (pos.x - mEnemies[0]->GetPosition().x);
//         float nearestdistY  = (pos.y - mEnemies[0]->GetPosition().y);
//         float nearestDistSq = nearestdistX * nearestdistX + nearestdistY * nearestdistY;
//         for(size_t i = 1; i < mEnemies.size(); i++)
//         {
//             float newdistX  = (pos.x - mEnemies[i]->GetPosition().x);
//             float newdistY  = (pos.y - mEnemies[i]->GetPosition().y);
//             float newDistSq = newdistX * newdistX + newdistY * newdistY;
//             if(newDistSq < nearestDistSq)
//             {
//                 nearestDistSq = newDistSq;
//                 nearest = mEnemies[i];
//             }
//         }
//     }
//     return nearest;
// }
// ------------- GAMEMODE METHODS ------------ //
// void Game::LoadRound()
// {
// }
// void Game::InitRound()
// {
//     gameRound.enemiesType.clear();
//     // Increment round id.
//     gameRound.rId++;
//     // Set the profit of the round according to round id.
//     switch (difficulty)
//     {
//     case GameDifficulty::EASY:
//         gameRound.profit = (int)round(floor(sqrt(50 * gameRound.rId) * 10));
//        break;
//     case GameDifficulty::MEDIUM:
//         gameRound.profit = (int)round(floor(sqrt(25 * gameRound.rId) * 8));
//         break;
//     case GameDifficulty::HARD:
//         gameRound.profit = (int)round(floor(sqrt(10 * gameRound.rId) * 5));
//         break;
//     default:
//         break;
//     }
//     // Generate enemies (listed by type).
//     gameRound.enemiesNumber = (int)round(ceil(3 * sqrt(10 * gameRound.rId)));
//     gameRound.remainingEnemies = gameRound.enemiesNumber;
//     gameRound.patternId = GetRandomValue(0,2);
//     for (int i = 0; i < gameRound.enemiesNumber; i++)
//     {
//         switch (gameRound.patternId)
//         {
//         case 0: // Classic pattern
//             gameRound.enemiesType.push_back(EnemyType::E_WEAK_ENEMY);
//             break;
//         case 1: // Classic pattern with healer and less strong enemies
//             if (i % 15 == 0) gameRound.enemiesType.push_back(EnemyType::E_STRONG_ENEMY);
//             if (i % 3 == 0)  gameRound.enemiesType.push_back(EnemyType::E_HEALER_ENEMY);
//             else             gameRound.enemiesType.push_back(EnemyType::E_WEAK_ENEMY);
//             break;
//         case 2: // Full strong enemy pattern
//             gameRound.enemiesType.push_back(EnemyType::E_STRONG_ENEMY);
//             break;    
//         default:
//             break;
//         }
//     } 
//     // Set the spawnrate according to round id and difficulty.
//     gameRound.spawnFrameCounter = gameRound.spawnedEnemyCounter = 0;
//     if (gameRound.rId >= 0 && gameRound.rId <= 25)       gameRound.spawnRate = 60;
//     else if (gameRound.rId > 25 && gameRound.rId <= 50)  gameRound.spawnRate = 50;
//     else if (gameRound.rId > 50 && gameRound.rId <= 75)  gameRound.spawnRate = 40;
//     else if (gameRound.rId > 75 && gameRound.rId <= 100) gameRound.spawnRate = 30;
// }
// void Game::RoundUpdate()
// {
//     // Spawning enemies according to spawn rate.
//     if (gameRound.remainingEnemies > 0)
//     {
//         if (gameRound.spawnedEnemyCounter < gameRound.enemiesNumber)
//         {
//             gameRound.spawnFrameCounter++;
//             if (gameRound.spawnFrameCounter == gameRound.spawnRate)
//             {
//                 new Enemy{this, gameRound.enemiesType[gameRound.spawnedEnemyCounter]};
//                 gameRound.spawnFrameCounter = 0;
//                 gameRound.spawnedEnemyCounter++;
//             }
//         }
//     }
//     // Initialize a new round if there are no remaining enemies.
//     else
//     {
//         if (player.hp > 0) player.money += gameRound.profit;
//         gameRound.rId++;
//         InitRound();
//     }
// 
// ----------- CORE RELATED METHODS ---------- //
// Private methods.
// TODO Gamemode loading methods executed during loading scene.
void Game::LoadData()
{
    player.Init();
    //InitRound();   //! TMP (this function is called for the first time by the launch round button)
}

// void Game::UnloadData()
// {
//     while(!mEntities.empty()) delete mEntities.back();
// }

// Public methods.

// void Game::UpdateEntities()
// {
//     //! TO COMMENT.
//     mUpdatingEntities = true;
//     for (auto entity : mEntities)
//     {
//         entity->Update(mDeltaTime);
//     }
//     mUpdatingEntities = false;

//     // Move any pending entity to mEntyties.
//     for (auto entity : mPendingEntities)
//         mEntities.emplace_back(entity);
//     mPendingEntities.clear();

//     // Add any dead entities to a temporary vector.
//     vector<Entity*> deadEntities;

//     for (auto entity : mEntities)
//         if (entity->GetState() == State::EDead)
//             deadEntities.emplace_back(entity);

//     // Delete dead entyties (which removes them from mEntyties).
//     for (auto entity : deadEntities) delete entity;
// }

void Game::UpdateGame(Ui& ui)
{
    mDeltaTime = GetFrameTime();

    switch (ui.sId)
    {
        case SceneId::LOADING:
            LoadData();
            ui.sId = SceneId::IN_GAME;
            break;

        case SceneId::IN_GAME:
            //RoundUpdate();
            //UpdateEntities();
            // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            // {
            //     Tower* tmp = new Tower{this, TowerType::E_STANDARD_TOWER};
            //     tmp->SetPosition((Vector2){GetScreenToWorld2D(GetMousePosition(), ui.inGameCamera).x / ui.renderScale,
            //                                GetScreenToWorld2D(GetMousePosition(), ui.inGameCamera).y / ui.renderScale});                                 
            // }
            break;

        default:
            break;
    }    
}