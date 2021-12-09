#include <iostream>
#include "raylib.h"

#include "resources.hpp"
#include "game.hpp"

int main(void)
{
    // INITIALIZATION.
    //-------------------------------------------
    InitWindow(1280, 970, "Project Jura");

    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    SetTargetFPS(60);
    
    InitAudioDevice();
    HideCursor();
    //ToggleFullscreen();
    
    Game game;
    Ui   ui(game);
    
    ui.Init();  

    //-------------------------------------------

    // MAIN GAME LOOP.
    //-------------------------------------------
    
    while(!WindowShouldClose()&& !game.needStop )
    {
        ui.Update();
        game.UpdateGame(ui);
  
        BeginDrawing();

            BeginMode2D(ui.inGameCamera);

                ClearBackground(WHITE);
                ui.DrawRender(game.player);

            EndMode2D();
            ui.DrawOverlay(game.player);

        EndDrawing();
    }
    //-------------------------------------------

    // DE-INITIALIZATION.
    //-------------------------------------------
    Resource::UnloadResource();
    UnloadRenderTexture(ui.gameRenderTexture);

    CloseAudioDevice();
    
    CloseWindow();
    //-------------------------------------------

    return 0;
}