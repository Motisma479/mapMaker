#include <iostream>

#include "resources.hpp"
#include "game.hpp"

#include "ui.hpp"

// ------------ LVL CONTAINER CLASS ----------- //

LevelContainer::LevelContainer(string _txt, Rectangle _rec, Texture2D _tex, Font _fnt)
              : txt(_txt)
              , rec(_rec)
              , tex(_tex)
              , fnt(_fnt)
{
}

bool LevelContainer::IsHovered(CursorState& state)
{
    if(CheckCollisionPointRec(GetMousePosition(), rec)) state = CursorState::POINTING;
    return CheckCollisionPointRec(GetMousePosition(), rec);
}

bool LevelContainer::IsClicked(CursorState& state)
{
    if (IsHovered(state) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return true;
    return false;
}

void LevelContainer::Display(CursorState& state, float scroller)
{
    // Update scroller.
    rec.x += scroller;

    // Drawing background.
    DrawTexturePro(Resource::GetTexture("./assets/sprites/frame.png"), {0, 0, 570, 420}, rec, {0, 0}, 0, WHITE);

    // Drawing thumbnail and title.
    DrawTexturePro(tex, {0, 0, (float)tex.width, (float)tex.height}, {rec.x + 20, rec.y + 20, 530, 310}, {0, 0}, 0, WHITE);
    DrawTextEx(fnt, txt.c_str(), {rec.x + rec.width / 2 - MeasureTextEx(fnt, txt.c_str(), 80, 0).x / 2, 
                                  rec.y + rec.height    - MeasureTextEx(fnt, txt.c_str(), 80, 0).y - 20 }
              , 80, 0, WHITE);

    // Is Hovered event.
    if (IsHovered(state))  DrawRectangleLinesEx({rec.x + 18, rec.y + 18, 532, 310}, 2, WHITE);
}


// -------------- BUTTON CLASS --------------- //

Button::Button()
      : isClickable(true)
      , displayTexture(false)
{
}

Button::Button(Rectangle _rec, Texture2D _tex) 
      : isClickable(true)
      , displayTexture(true)
      , rec(_rec)
      , tex(_tex)
{
}

Button::Button(int _fs, string _text, Color _tc, Rectangle _rec, Texture2D _tex, Font _font)
      : isClickable(true)
      , displayTexture(true)
      , fontSize(_fs)
      , text(_text)
      , textColor(_tc)
      , rec(_rec)
      , tex(_tex)
      , font(_font)
{
}

bool Button::IsHovered(CursorState& state)
{
    if(CheckCollisionPointRec(GetMousePosition(), rec)) state = CursorState::POINTING;
    return CheckCollisionPointRec(GetMousePosition(), rec);
}

bool Button::IsClicked(CursorState& state)
{
    if(isClickable && IsHovered(state) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return true;
    return false;
}

void Button::Draw(CursorState& state)
{
    // Texture drawing.
    if(displayTexture)
    {
        if (IsHovered(state))
        {
            DrawTexturePro(tex, {0, 0, (float)tex.width, (float)tex.height}, rec, {0, 0}, 0, {255, 255, 255, 200});
            DrawTextPro(font,text.c_str(),
                    {rec.x + rec.width  / 2 - MeasureTextEx(font, text.c_str(), fontSize, 0).x / 2,
                    rec.y + rec.height / 2 - MeasureTextEx(font, text.c_str(), fontSize, 0).y / 2},
                    {0, 0}, 0, fontSize, 0, YELLOW);
        }
        else
        {
            DrawTexturePro(tex, {0, 0, (float)tex.width, (float)tex.height}, rec, {0, 0}, 0, WHITE);
            // Text display.
            DrawTextPro(font,text.c_str(),
                    {rec.x + rec.width  / 2 - MeasureTextEx(font, text.c_str(), fontSize, 0).x / 2,
                    rec.y + rec.height / 2 - MeasureTextEx(font, text.c_str(), fontSize, 0).y / 2},
                    {0, 0}, 0, fontSize, 0, textColor);
        }
    }

    
    
}
/******************\
 * TexturedButton * 
\******************/
TexturedButton::TexturedButton()
      : isClickable(true)
      , displayTexture(false)
{
}

TexturedButton::TexturedButton(Rectangle _rec, Texture2D _tex) 
      : isClickable(true)
      , displayTexture(true)
      , rec(_rec)
      , buttonTexture(_tex)
{
}

bool TexturedButton::IsHovered(CursorState& state)
{
    if(CheckCollisionPointRec(GetMousePosition(), rec)) state = CursorState::POINTING;
    return CheckCollisionPointRec(GetMousePosition(), rec);
}

bool TexturedButton::IsClicked(CursorState& state)
{
    if(isClickable && IsHovered(state) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        
        return true;
    };
    
    return false;
}

void TexturedButton::Draw(CursorState& state)
{
    // Texture drawing.
    if(displayTexture)
    {
        
        if (IsHovered(state))
        {
            DrawTexturePro(buttonTexture, {0, 0, (float)buttonTexture.width, (float)buttonTexture.height}, rec, {0, 0}, 0, { 185, 217, 255, 255 });
        }
        else
        {
            DrawTexturePro(buttonTexture, {0, 0, (float)buttonTexture.width, (float)buttonTexture.height}, rec, {0, 0}, 0, WHITE);
        }
    }
    if (isActive)
    {
        DrawRectanglePro(rec, {0, 0}, 0, {255,0,0,50});
        DrawRectangleLinesEx(rec,4,RED);
    }

    
    
}

/******************\
 * TilePaint * 
\******************/
TilePaint::TilePaint()
      : isClickable(true)
      , displayTexture(false)
{
}

TilePaint::TilePaint(Rectangle _rec, Texture2D _tex, int sizeOfTile) 
      : isClickable(true)
      , displayTexture(true)
      , tilesize(sizeOfTile)
      , rec(_rec)
      , tileTexture(_tex)
{
    for (int i = 0; tileTexture.height / tilesize > i; i++)
    {
        for (int j = 0; tileTexture.width / tilesize > j; j++)
        {
            tileList.emplace_back((Rectangle){(float)((rec.width/tileTexture.width)*tilesize)*j + rec.x,
                                            (float)((rec.height/tileTexture.height)*tilesize)*i + rec.y,
                                            (rec.width/tileTexture.width)*tilesize,
                                            ((rec.height/tileTexture.height)*tilesize)});
            originalPostion.emplace_back((Vector2){(float)j*tilesize,(float)i*tilesize});
        }
    }
    
}

bool TilePaint::IsHovered(CursorState& state)
{
    if(CheckCollisionPointRec(GetMousePosition(), rec)) state = CursorState::POINTING;
    return CheckCollisionPointRec(GetMousePosition(), rec);
}

bool TilePaint::IsRClicked(CursorState& state)
{
    if(isClickable && IsHovered(state) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
        
        return true;
    };
    
    return false;
}
bool TilePaint::IsLClicked(CursorState& state)
{
    if(isClickable && IsHovered(state) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        
        return true;
    };
    
    return false;
}

void TilePaint::Draw(CursorState& state)
{
    // Texture drawing.
    if(displayTexture)
    {
        
        if (IsHovered(state))
        {
            DrawTexturePro(tileTexture, {0, 0, (float)tileTexture.width, (float)tileTexture.height}, rec, {0, 0}, 0, WHITE);
            for (int i = 0; i<((tileTexture.width/tilesize)*(tileTexture.height/tilesize)); i++)
            {
                        
                //DrawRectangleLinesEx({(float)((rec.width/tileTexture.width)*tilesize)*j + rec.x,(float)((rec.height/tileTexture.height)*tilesize)*i + rec.y,(rec.width/tileTexture.width)*tilesize,((rec.height/tileTexture.height)*tilesize)},1,DARKGRAY);
                
                if(CheckCollisionPointRec(GetMousePosition(), tileList[i])){
                        DrawRectanglePro(tileList[i], {0, 0}, 0, {255,0,0,50});
                        DrawRectangleLinesEx(tileList[i],3
                        ,RED);
                    
                }
                    
            }
        }
        else
        {
            DrawTexturePro(tileTexture, {0, 0, (float)tileTexture.width, (float)tileTexture.height}, rec, {0, 0}, 0, WHITE);
        }
        DrawRectangleLinesEx(rec,4,DARKGRAY);

        
        for (int i = 0; i<((tileTexture.width/tilesize)*(tileTexture.height/tilesize)); i++)
        {
                
                //DrawRectangleLinesEx({(float)((rec.width/tileTexture.width)*tilesize)*j + rec.x,(float)((rec.height/tileTexture.height)*tilesize)*i + rec.y,(rec.width/tileTexture.width)*tilesize,((rec.height/tileTexture.height)*tilesize)},1,DARKGRAY);
                DrawRectangleLinesEx(tileList[i],1,DARKGRAY);
            
        }
       

    }


    /* if (isActive)
    {
        DrawRectanglePro(rec, {0, 0}, 0, {255,0,0,50});
        DrawRectangleLinesEx(rec,4,RED);
    } */

    
    
}

// ----------------- UI CLASS ---------------- //

Ui::Ui(Game& game)
  : gameRef(game)
{
}

void Ui::Init()
{
    // Local vraiables.
    int offset_x = 0;

    // Ui render texture initialization.
    gameRenderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    
    // Ui textures initialization.
    uiTexture[0]  = Resource::GetTexture("./assets/sprites/cheese0.png");
    uiTexture[1]  = Resource::GetTexture("./assets/sprites/cheese1.png");
    uiTexture[2]  = Resource::GetTexture("./assets/sprites/cheese2.png");
    uiTexture[3]  = Resource::GetTexture("./assets/sprites/cheese3.png");
    uiTexture[4]  = Resource::GetTexture("./assets/sprites/cheese4.png");
    uiTexture[5]  = Resource::GetTexture("./assets/sprites/logo.png");
    uiTexture[6]  = Resource::GetTexture("./assets/sprites/background0.png");
    uiTexture[7]  = Resource::GetTexture("./assets/sprites/game_logo.png"); 
    uiTexture[8]  = Resource::GetTexture("./assets/sprites/button0.png");
    uiTexture[9]  = Resource::GetTexture("./assets/sprites/cursor0.png");
    uiTexture[10] = Resource::GetTexture("./assets/sprites/cursor1.png");
    uiTexture[11] = Resource::GetTexture("./assets/sprites/cursor2.png");
    uiTexture[12] = Resource::GetTexture("./assets/sprites/eraser.png");
    uiTexture[13] = Resource::GetTexture("./assets/sprites/write.png");
    uiTexture[14] = Resource::GetTexture("./assets/sprites/save.png");
    uiTexture[15] = Resource::GetTexture("./assets/tilemaps/tiles.png");
    uiTexture[16] = Resource::GetTexture("./assets/sprites/zoomPlus.png");
    uiTexture[17] = Resource::GetTexture("./assets/sprites/zoomMinus.png");
    

    // Ui sfx initialization.
    uiSfx[0] = Resource::GetSound("./assets/sfx/crunch.ogg");
    uiSfx[1] = Resource::GetSound("./assets/sfx/dream.ogg");

    // Ui font initialization.
    uiFont[0] = Resource::GetFont("./assets/fonts/molten-bites.ttf", 80);

    // Check available levels.
    levelsMetadata = Resource::GetAvailableLevels();

    // Level container creation.
    for (auto it : levelsMetadata)
    {
        LevelContainer tmp(it.first.c_str(), 
                          {(float) GetScreenWidth() / 2 - 285 + offset_x, (float)GetScreenHeight() / 2 - 200, 570, 420},
                          it.second,
                          uiFont[0]);
        levelsContainers.push_back(tmp);
        offset_x += 620;
    }
}

void Ui::DrawIntro()
{
    if(IsKeyPressed(KEY_SPACE)||IsKeyPressed(KEY_KP_ENTER)||IsKeyPressed(KEY_ENTER)) sId = SceneId::MAIN_MENU;
    // Intro sequence.
    if (aIntro.key < aIntro.end)
    {
        if (aIntro.key < 120)
        {
            DrawTexturePro(uiTexture[0], {0, 0, 27, 27}, 
                {(float)GetScreenWidth()  / 2 - (float)256 / 2, 
                 (float)GetScreenHeight() / 2 - (float)256 / 2,
                 256, 256},
                {0, 0}, 0, WHITE);
        }
        else if (aIntro.key >= 120 && aIntro.key < 160)
        {
            DrawTexturePro(uiTexture[1], {0, 0, 27, 27}, 
                {(float)GetScreenWidth()  / 2 - (float)256 / 2, 
                 (float)GetScreenHeight() / 2 - (float)256 / 2,
                 256, 256},
                {0, 0}, 0, WHITE);
        }
        else if (aIntro.key >= 160 && aIntro.key < 180)
        {
            DrawTexturePro(uiTexture[2], {0, 0, 27, 27}, 
                {(float)GetScreenWidth()  / 2 - (float)256 / 2, 
                 (float)GetScreenHeight() / 2 - (float)256 / 2,
                 256, 256},
                {0, 0}, 0, WHITE);
        }
        else if (aIntro.key >= 180 && aIntro.key < 190)
        {
            DrawTexturePro(uiTexture[3], {0, 0, 27, 27}, 
                {(float)GetScreenWidth()  / 2 - (float)256 / 2, 
                 (float)GetScreenHeight() / 2 - (float)256 / 2,
                 256, 256},
                {0, 0}, 0, WHITE);
        }
        else if (aIntro.key >= 190 && aIntro.key < 230)
        {
            DrawTexturePro(uiTexture[4], {0, 0, 27, 27}, 
                {(float)GetScreenWidth()  / 2 - (float)256 / 2, 
                 (float)GetScreenHeight() / 2 - (float)256 / 2,
                 256, 256},
                {0, 0}, 0, WHITE);
        }
        else
        {
            DrawTexturePro(uiTexture[5], {0, 0, 710, 200}, 
                {(float)GetScreenWidth()  / 2 - 355, 
                 (float)GetScreenHeight() / 2 - 100,
                 710, 200},
                {0, 0}, 0, WHITE);
        }
        aIntro.key++;
    }
    else
    {
        sId = SceneId::MAIN_MENU;
    }
        
    // SFX played in this animation.
    if (aIntro.key == 120) PlaySoundMulti(uiSfx[0]);
    if (aIntro.key == 160) PlaySoundMulti(uiSfx[0]);
    if (aIntro.key == 180) PlaySoundMulti(uiSfx[0]);
    if (aIntro.key == 190) PlaySoundMulti(uiSfx[0]);
    if (aIntro.key == 230) PlaySoundMulti(uiSfx[0]);
    if (aIntro.key == 250) PlaySoundMulti(uiSfx[1]);
}

void Ui::DrawMainMenu()
{
    // Draw game logo and background.
    DrawTexturePro(uiTexture[6], {0, 0, 1024, 768}, 
                  {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, 
                  {0, 0}, 0, WHITE);
    DrawTexturePro(uiTexture[7], {0, 0, 518, 89}, 
                   {(float)GetScreenWidth() / 2 - 428, (float)GetScreenHeight() / 3 - 150, 518, 89},
                   {0, 0}, 0, WHITE);
    DrawTextPro(uiFont[0],"Map Maker",(Vector2){(float)GetScreenWidth() / 2 - MeasureTextEx(uiFont[0],"Map Maker",225,1).x / 2, (float)GetScreenHeight() / 3 - 350},(Vector2){0,0},0,225 ,1,RED);
    
    
    // Buttons creation.
    Button b_play(80, "Start Editor", WHITE, 
                 {(float)GetScreenWidth() /2 - 225,
                  (float)GetScreenHeight() / 3,
                  450  ,
                  100},
                 uiTexture[8], uiFont[0]);
    Button b_quit(80, "QUIT", WHITE,
                   {(float)GetScreenWidth() /2 - 125,
                    (float)GetScreenHeight() / 3 + 150, 
                    250,
                    100},
                    uiTexture[8], uiFont[0]);
    
    // Buttons draw.
    
    b_play.Draw(cState);
    b_quit.Draw(cState);

    // Buttons scripting.
    if (b_play.IsClicked(cState)) sId = SceneId::SELECT_MENU;
    if (b_quit.IsClicked(cState)) gameRef.needStop = true;
}

void Ui::DrawSelectMenu()
{  
    Button widthPlus(80, "+", WHITE, 
                 {(float)GetScreenWidth() /2 - 425,
                  (float)GetScreenHeight() / 3,
                  200  ,
                  100},
                 uiTexture[8], uiFont[0]);
    Button widthMinus(80, "-", WHITE, 
                 {(float)GetScreenWidth() /2 + 225,
                  (float)GetScreenHeight() / 3,
                  200  ,
                  100},
                 uiTexture[8], uiFont[0]);
    Button heightPlus(80, "+", WHITE, 
                 {(float)GetScreenWidth() /2 - 425,
                  (float)GetScreenHeight() / 3+250,
                  200  ,
                  100},
                 uiTexture[8], uiFont[0]);
    Button heightMinus(80, "-", WHITE, 
                 {(float)GetScreenWidth() /2 + 225,
                  (float)GetScreenHeight() / 3+250,
                  200  ,
                  100},
                 uiTexture[8], uiFont[0]);
    Button validate(80, "Validate", WHITE, 
                 {(float)GetScreenWidth() /2 - 225,
                  (float)GetScreenHeight() / 3 + 500,
                  450  ,
                  100},
                 uiTexture[8], uiFont[0]);

        fileData.textBox.x = (float)GetScreenWidth() /2 -200;
        fileData.textBox.y = (float)GetScreenHeight() /2 - 380;
        fileData.textBox.width = 400;
        fileData.textBox.height = 80;

    DrawTexturePro(uiTexture[6], {0, 0, 1024, 768}, {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0, 0}, 0, WHITE);
    DrawTextEx(uiFont[0], "File Information", {(float)GetScreenWidth() / 2 - MeasureTextEx(uiFont[0], "File Information", 100, 0).x / 2, 100}, 100, 0, WHITE);
    
    DrawText("File name:", (float)GetScreenWidth() /2 -200, (float)GetScreenHeight() /2 - 420, 30, WHITE);

    DrawRectangleRec(fileData.textBox, LIGHTGRAY);

    if (fileData.canWriteInBox) DrawRectangleLines((int)fileData.textBox.x, (int)fileData.textBox.y, (int)fileData.textBox.width, (int)fileData.textBox.height, RED);
    else DrawRectangleLines((int)fileData.textBox.x, (int)fileData.textBox.y, (int)fileData.textBox.width, (int)fileData.textBox.height, DARKGRAY);
    DrawText(fileData.name, (int)fileData.textBox.x + 5, (int)fileData.textBox.y + 8, 65, MAROON);
    DrawText(TextFormat("%i/%i", fileData.letterCount, 9), (float)GetScreenWidth() /2 +215, (float)GetScreenHeight() /2 - 320, 25, GRAY);
    if (fileData.canWriteInBox)
    {
        if (fileData.letterCount < 9)
        {
            // Draw blinking underscore char
            DrawText("_", (int)fileData.textBox.x + 8 + MeasureText(fileData.name, 65), (int)fileData.textBox.y + 12, 65, MAROON);
        }
    }
    DrawText("Width:", GetScreenWidth() /2 - MeasureTextEx(GetFontDefault(), "Width", 35, 0).x/2, GetScreenHeight() / 3 - 25, 35, WHITE);
    widthMinus.Draw(cState);
    DrawText(TextFormat("%d",fileData.width), GetScreenWidth() /2 - MeasureTextEx(GetFontDefault(), TextFormat("%d",fileData.width), 46, 0).x/2, GetScreenHeight() / 3+20, 46, WHITE);
    widthPlus.Draw(cState);


    DrawText("Height:", GetScreenWidth() /2 - MeasureTextEx(GetFontDefault(), "Height", 35, 0).x/2, GetScreenHeight() / 3+230, 35, WHITE);
    heightMinus.Draw(cState);
    DrawText(TextFormat("%d",fileData.height), GetScreenWidth() /2 - MeasureTextEx(GetFontDefault(), TextFormat("%d",fileData.height), 46, 0).x/2, GetScreenHeight() / 3+275, 46, WHITE);
    heightPlus.Draw(cState);
            
    if (fileData.saveTryEmpty)
    {
        DrawText("Please name your map.", (float)GetScreenWidth() /2 - 225,
                  (float)GetScreenHeight() / 3 + 465, 30, RED);
    }
    if (fileData.saveTryIncorect)
    {
        DrawText("Please use only ( 0-9 a-z A-Z _ ). ", (float)GetScreenWidth() /2 - 225,
                  (float)GetScreenHeight() / 3 + 465, 30, RED);
    }
    validate.Draw((cState));
    
    /***********\
     * TextBox * 
    \***********/
    if (CheckCollisionPointRec(GetMousePosition(), fileData.textBox) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) fileData.canWriteInBox = true;
        else if (!CheckCollisionPointRec(GetMousePosition(), fileData.textBox) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) fileData.canWriteInBox = false;
        if (fileData.canWriteInBox)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (fileData.letterCount < 9))
                {
                    fileData.name[fileData.letterCount] = (char)key;
                    fileData.name[fileData.letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    fileData.letterCount++;
                }

            key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                fileData.letterCount--;
                if (fileData.letterCount < 0) fileData.letterCount = 0;
                fileData.name[fileData.letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    /***********\
     *  width  * 
    \***********/
    if (widthPlus.IsClicked(cState))
    {
        fileData.width++;
        if(fileData.width>50) fileData.width=50;
    }
    if (widthMinus.IsClicked(cState))
    {
        fileData.width--;
        if(fileData.width<3) fileData.width=3;
    } 
    /***********\
     * height  * 
    \***********/
    if (heightPlus.IsClicked(cState))
    {
        fileData.height++;
        if(fileData.height>50) fileData.height=50;
    }
    if (heightMinus.IsClicked(cState))
    {
        fileData.height--;
        if(fileData.height<3) fileData.height=3;
    }

       
        
        if(validate.IsClicked(cState)){
                if (fileData.name[0]!='\0')
                {
                     for (int i = 0; fileData.name[i]!='\0'; i++)
                    {
                        if ((fileData.name[i] >= 48 && fileData.name[i] <= 57)||(fileData.name[i] >= 65 && fileData.name[i] <= 90)||(fileData.name[i] >= 97 && fileData.name[i] <= 122)||fileData.name[i] == 95)
                        {
                            fileData.saveTryIncorect =false;
                        }else{
                            fileData.saveTryIncorect =true;
                            break;
                        }
                        
                    }
                    if (!fileData.saveTryIncorect)
                    {
                        
                        hasPutInformation=true;
                      
                    }
                    fileData.saveTryEmpty = false;
                    
                }else{
                    fileData.saveTryEmpty = true;
                }

            }

    if (hasPutInformation)
    {
        sId = SceneId::LOADING;
    }
    

}

void Ui::DrawInGame()
{
    // Drawing tilemap.
    gameRef.tm.Draw();

    // Drawing entities.
    //for (auto entity : gameRef.GetEntities()) entity->Draw();

}

void Ui::DrawHUD(Player player)
{
    TilePaint paint({0,(float)(GetScreenHeight()-(uiTexture[15].height *1.5)),128*1.5,224*1.5},uiTexture[15], 32);

    TexturedButton saver({0,0,50,50},uiTexture[14]);
    
    TexturedButton eraser({0,100,50,50},uiTexture[12]);
    if (selectedTool == 2) eraser.isActive = true;

    TexturedButton writer({0,50,50,50},uiTexture[13]);
    if (selectedTool == 1) writer.isActive = true;

    TexturedButton zoomPlus({50,0,50,50},uiTexture[16]);
    TexturedButton zoomMinus({100,0,50,50},uiTexture[17]);

    

    //! DEBUG ZONE ========================================================

    // DrawText(TextFormat("ROUND:\nrId: %d\npatternId: %d\nprofit: %d\nremaning: %d\n spawned: %d\nframerate: %d/%d\n", 
    //                     gameRef.gameRound.rId,
    //                     gameRef.gameRound.patternId,
    //                     gameRef.gameRound.profit,
    //                     gameRef.gameRound.remainingEnemies,
    //                     gameRef.gameRound.spawnedEnemyCounter,
    //                     gameRef.gameRound.spawnFrameCounter,
    //                     gameRef.gameRound.spawnRate),
    //         10, 10, 25, RED);

    //! ===================================================================

    //TODO REMOVE
   /*  DrawTexturePro(uiTexture[13], {0, 0, (float)uiTexture[13].width, (float)uiTexture[13].height}, 
                  {0, 
                   (float)GetScreenHeight() - uiTexture[13].height * GetScreenWidth() / uiTexture[13].width, 
                   (float)GetScreenWidth(), 
                   (float)uiTexture[13].height * GetScreenWidth() / uiTexture[13].width}, 
                   {0, 0}, 0, WHITE); */
        DrawTexturePro(paint.tileTexture,{paint.originalPostion[onRightClick].x,paint.originalPostion[onRightClick].y,32,32},{paint.rec.x+50,paint.rec.y-60,50,50},{0,0},0,WHITE);
        DrawRectangleLinesEx({paint.rec.x+50,paint.rec.y-60,50,50},3,DARKGRAY);
        DrawTexturePro(paint.tileTexture,{paint.originalPostion[onLeftClick].x,paint.originalPostion[onLeftClick].y,32,32},{paint.rec.x+15,paint.rec.y-80,50,50},{0,0},0,WHITE);
        DrawRectangleLinesEx({paint.rec.x+15,paint.rec.y-80,50,50},3,DARKGRAY);
        
    paint.Draw(cState);
    

    if (writer.IsClicked(cState))
    {
        selectedTool = 1;
        printf("clicked");
        
    }else if (eraser.IsClicked(cState))
    {
        selectedTool = 2;
        eraser.isActive = true ;
    }
    if (zoomPlus.IsClicked(cState))
    {
        inGameCamera.zoom += 0.1;
        if (inGameCamera.zoom > 5.0)
        {
            inGameCamera.zoom = 5.0;
        }
        
    }
    if (zoomMinus.IsClicked(cState))
    {
        inGameCamera.zoom -= 0.1;
        if (inGameCamera.zoom < 1.0)
        {
            inGameCamera.zoom = 1.0;
        }
        
    }
    
    if (paint.IsRClicked(cState))
    {
        for (int i = 0; i<((paint.tileTexture.width/paint.tilesize)*(paint.tileTexture.height/paint.tilesize)); i++)
        {
            if(CheckCollisionPointRec(GetMousePosition(), paint.tileList[i])){
                onRightClick = i;
            }
        }
        cout <<onRightClick<< endl;
    }
    if (paint.IsLClicked(cState))
    {
        for (int i = 0; i<((paint.tileTexture.width/paint.tilesize)*(paint.tileTexture.height/paint.tilesize)); i++)
        {
            if(CheckCollisionPointRec(GetMousePosition(), paint.tileList[i])){
                onLeftClick = i;
                        
            }
        }
        cout <<onLeftClick<< endl;
    }
    

    saver.Draw(cState);
    writer.Draw(cState);
    eraser.Draw(cState);
    zoomPlus.Draw(cState);
    zoomMinus.Draw(cState);
    
}

void Ui::DrawOverlay(Player player)
{
    // Draw scene according to the current scene ID.
   switch (sId)
    {
    case SceneId::INTRO:
        DrawIntro();
        break;

    case SceneId::MAIN_MENU:
        DrawMainMenu();
        break;

    case SceneId::SELECT_MENU:
        DrawSelectMenu();
        break;

    case SceneId::IN_GAME:
        DrawHUD(player);
        break;
    
    default:
        break;
    }   

    // Draw cursor according to it state.
    DrawTextureEx(uiTexture[9 + (int)cState], GetMousePosition(), 0, 3, WHITE);
}

void Ui::Update()
{
    // Mouse position update;
    mouseWorldPosition = GetScreenToWorld2D(GetMousePosition(), inGameCamera);
    
    // Cursor states update.
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && cState == CursorState::POINTING)
    {
        cState =  CursorState::NORMAL;
    }
    else if ((IsMouseButtonDown(MOUSE_BUTTON_LEFT)  && gameRef.player.isDragging) ||
             (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && GetGestureDetected() == GESTURE_DRAG))
    {
        cState = CursorState::GRABBING;
    }
    else
    {
        cState =  CursorState::NORMAL;
    }
    
    // Scenes update.
    switch (sId)
    {
    case SceneId::LOADING:
        gameRef.tm.Init(fileData.width,fileData.height);
        inGameCamera.zoom = 3.0f;
        break;

    case SceneId::IN_GAME:
        // Camera update.
        // if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && GetGestureDetected() == GESTURE_DRAG)
        // {            
        //     inGameCamera.target.x += -GetGestureDragVector().x * 32;
        //     inGameCamera.target.y += -GetGestureDragVector().y * 32;
            
        //     if (IsKeyDown(KEY_LEFT))  
        //         inGameCamera.offset.x += 300 * GetFrameTime();
        //         inGameCamera.target.x -= 30;
        //     if (IsKeyDown(KEY_RIGHT) && inGameCamera.offset.x >= -gameRef.tm.width * TILE_SIZE + 15)
        //         inGameCamera.offset.x -= 300 * GetFrameTime();
        //     if (IsKeyDown(KEY_UP) && inGameCamera.offset.y < -10)
        //         inGameCamera.offset.y += 300 * GetFrameTime();
        //     if (IsKeyDown(KEY_DOWN) && inGameCamera.offset.y >= -gameRef.tm.height * (TILE_SIZE + 2)  - uiTexture[6].height * (int)inGameCamera.zoom + 15)
        //         inGameCamera.offset.y -= 300 * GetFrameTime();
        // }


        //? NOTE: Camera offset is inversed (e.g x=1 -> offset.x = -1)
        // Camera borders (including HUD size)
        if(IsKeyDown(KEY_LEFT)  && inGameCamera.offset.x < -7)  
            inGameCamera.offset.x += 300 * GetFrameTime();
        if(IsKeyDown(KEY_RIGHT)  && inGameCamera.offset.x >= GetScreenWidth() - gameRef.tm.width * TILE_SIZE * inGameCamera.zoom + 15)
            inGameCamera.offset.x -= 300 * GetFrameTime();
        if(IsKeyDown(KEY_UP) && inGameCamera.offset.y < -7)
            inGameCamera.offset.y += 300 * GetFrameTime();
        if(IsKeyDown(KEY_DOWN) && inGameCamera.offset.y >= GetScreenHeight() - gameRef.tm.height * TILE_SIZE * inGameCamera.zoom)
            inGameCamera.offset.y -= 300 * GetFrameTime();
        break;
    
    default:
        break;
    }       
     
}

void Ui::DrawRender(Player player)
{ 
   // Draw scene according to the current scene ID.
   switch (sId)
    {
    case SceneId::IN_GAME:
        DrawInGame();
        break;
    
    default:
        break;
    }
}
