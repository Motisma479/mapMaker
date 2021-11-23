#include "common.hpp"
#include"draw.hpp"

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "mapMaker");
    common::Game game;

    game.gameState=0;

    game.start.bu = new common::Button();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        draw::draw(game);
    }

    CloseWindow();
    delete(game.start.bu );

    return 0;
}