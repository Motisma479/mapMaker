#include <algorithm>
#include <iostream>

#include "ui.hpp"
#include "resources.hpp"

#include "game.hpp"

using namespace std;

//* GAME CLASS ==================================
// --------------- CONSTRUCTOR --------------- //

Game::Game()
    : mIsRunning(true)
    , mUpdatingEntities(false)
    , mSpawnTower(false)
{}

// ----------- CORE RELATED METHODS ---------- //

// Private methods.
void Game::UpdateGame(Ui& ui)
{
    mDeltaTime = GetFrameTime();

    switch (ui.mSId)
    {
        case SceneId::LOADING:
            ui.mSId = SceneId::IN_GAME;
            break;

        default:
            break;
    }    
}