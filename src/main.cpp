#include <iostream>
#include "raylib.h"

#include "resources.hpp"
#include "game.hpp"

int main(void)
{
    // INITIALIZATION.
    //-------------------------------------------
    InitWindow(1280, 970, "Level Editor");

    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    SetTargetFPS(60);
    
    Game game;
    Ui   ui(game);
    ui.Init();  

    //-------------------------------------------

    // MAIN GAME LOOP.
    //-------------------------------------------
    
    while(!WindowShouldClose() && !game.needStop )
    {
        ui.Update();
        game.UpdateGame(ui);
  
        BeginDrawing();

            BeginMode2D(ui.mInGameCamera);

                ClearBackground(WHITE);
                ui.DrawRender();

            EndMode2D();
            ui.DrawOverlay();

        EndDrawing();
    }
    //-------------------------------------------

    // DE-INITIALIZATION.
    //-------------------------------------------
    Resource::UnloadResource();
    
    CloseWindow();
    //-------------------------------------------

    return 0;
}