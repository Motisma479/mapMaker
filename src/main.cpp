#include "common.hpp"
#include"draw.hpp"

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "mapMaker");
    common::Game game;

    game.gameState=0;

    game.start.quit = new common::Button();
    game.start.start = new common::Button();
    game.editor.fileInfo.heightMinus = new common::Button();
    game.editor.fileInfo.heightPlus = new common::Button();
    game.editor.fileInfo.widthMinus = new common::Button();
    game.editor.fileInfo.widthPlus = new common::Button();

    SetTargetFPS(60);

    while (!WindowShouldClose() && !game.start.quit->isPressed)
    {
        game.mousePoint = GetMousePosition();
        draw::draw(game);
    }

    CloseWindow();
    delete(game.start.quit );

    delete(game.start.start );

    delete(game.editor.fileInfo.heightMinus );
    delete(game.editor.fileInfo.heightPlus );
    delete(game.editor.fileInfo.widthMinus );
    delete(game.editor.fileInfo.widthPlus );

    return 0;
}