#include <iostream>

#include "resources.hpp"
#include "game.hpp"

#include "ui.hpp"

//* BUTTON CLASS ================================
Button::Button()
      : isClickable(true)
      , displayTexture(false)
{}

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

//* TILEPAINT CLASS =============================
TilePaint::TilePaint()
      : isClickable(true)
      , displayTexture(false)
{}

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
            tileList.emplace_back((Rectangle){(float)((rec.width / tileTexture.width) * tilesize) * j + rec.x,
                                              (float)((rec.height / tileTexture.height) * tilesize) * i + rec.y,
                                              (rec.width / tileTexture.width) * tilesize,
                                              ((rec.height / tileTexture.height) * tilesize)});

            originalPostion.emplace_back((Vector2){(float)j*tilesize, (float)i*tilesize});
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
                if(CheckCollisionPointRec(GetMousePosition(), tileList[i]))
                {
                    DrawRectanglePro(tileList[i], {0, 0}, 0, {255,0,0,50});
                    DrawRectangleLinesEx(tileList[i], 3 ,RED);
                }
                    
            }
        }
        else
        {
            DrawTexturePro(tileTexture, {0, 0, (float)tileTexture.width, (float)tileTexture.height}, rec, {0, 0}, 0, WHITE);
        }

        DrawRectangleLinesEx(rec, 4, DARKGRAY);

        for (int i = 0; i<((tileTexture.width/tilesize)*(tileTexture.height/tilesize)); i++)
            DrawRectangleLinesEx(tileList[i],1,DARKGRAY);      
    }   
}

// ----------------- UI CLASS ---------------- //

Ui::Ui(Game& game)
  : mGameRef(game)
{
    mHudIsActive   = true;
    mUiHovered     = false;
    mSId           = SceneId::INTRO;
    aIntro        = {0, 450};
    cState        = CursorState::NORMAL;
    mInGameCamera = {{0, 0}, {0, 0}, 0, 1};
}

void Ui::Init()
{
    // Ui textures initialization.
    mUiTexture[0]  = Resource::GetTexture("./assets/sprites/cheese0.png");
    mUiTexture[1]  = Resource::GetTexture("./assets/sprites/cheese1.png");
    mUiTexture[2]  = Resource::GetTexture("./assets/sprites/cheese2.png");
    mUiTexture[3]  = Resource::GetTexture("./assets/sprites/cheese3.png");
    mUiTexture[4]  = Resource::GetTexture("./assets/sprites/cheese4.png");
    mUiTexture[5]  = Resource::GetTexture("./assets/sprites/logo.png");
    mUiTexture[6]  = Resource::GetTexture("./assets/sprites/background0.png");
    mUiTexture[7]  = Resource::GetTexture("./assets/sprites/game_logo.png"); 
    mUiTexture[8]  = Resource::GetTexture("./assets/sprites/button0.png");
    mUiTexture[9]  = Resource::GetTexture("./assets/sprites/cursor0.png");
    mUiTexture[10] = Resource::GetTexture("./assets/sprites/cursor1.png");
    mUiTexture[11] = Resource::GetTexture("./assets/sprites/cursor2.png");
    mUiTexture[12] = Resource::GetTexture("./assets/sprites/eraser.png");
    mUiTexture[13] = Resource::GetTexture("./assets/sprites/write.png");
    mUiTexture[14] = Resource::GetTexture("./assets/sprites/save.png");
    mUiTexture[15] = Resource::GetTexture("./assets/tilemaps/tiles.png");
    mUiTexture[16] = Resource::GetTexture("./assets/sprites/zoomPlus.png");
    mUiTexture[17] = Resource::GetTexture("./assets/sprites/zoomMinus.png");
    mUiTexture[18] = Resource::GetTexture("./assets/sprites/information.png");
    mUiTexture[19] = Resource::GetTexture("./assets/sprites/flag.png");

    // Ui sfx initialization.
    mUiSfx[0] = Resource::GetSound("./assets/sfx/crunch.ogg");
    mUiSfx[1] = Resource::GetSound("./assets/sfx/dream.ogg");

    // Ui font initialization.
    mUiFont = Resource::GetFont("./assets/fonts/molten-bites.ttf", 80);
}

void Ui::DrawIntro()
{
    if(IsKeyPressed(KEY_SPACE)||IsKeyPressed(KEY_KP_ENTER)||IsKeyPressed(KEY_ENTER)) mSId = SceneId::MAIN_MENU;
    // Intro sequence.
    if (aIntro.key < aIntro.end)
    {
        if (aIntro.key < 120)
        {
            DrawTexturePro(mUiTexture[0], {0, 0, 27, 27}, 
                {(float)GetScreenWidth()  / 2 - (float)256 / 2, 
                 (float)GetScreenHeight() / 2 - (float)256 / 2,
                 256, 256},
                {0, 0}, 0, WHITE);
        }
        else if (aIntro.key >= 120 && aIntro.key < 160)
        {
            DrawTexturePro(mUiTexture[1], {0, 0, 27, 27}, 
                {(float)GetScreenWidth()  / 2 - (float)256 / 2, 
                 (float)GetScreenHeight() / 2 - (float)256 / 2,
                 256, 256},
                {0, 0}, 0, WHITE);
        }
        else if (aIntro.key >= 160 && aIntro.key < 180)
        {
            DrawTexturePro(mUiTexture[2], {0, 0, 27, 27}, 
                {(float)GetScreenWidth()  / 2 - (float)256 / 2, 
                 (float)GetScreenHeight() / 2 - (float)256 / 2,
                 256, 256},
                {0, 0}, 0, WHITE);
        }
        else if (aIntro.key >= 180 && aIntro.key < 190)
        {
            DrawTexturePro(mUiTexture[3], {0, 0, 27, 27}, 
                {(float)GetScreenWidth()  / 2 - (float)256 / 2, 
                 (float)GetScreenHeight() / 2 - (float)256 / 2,
                 256, 256},
                {0, 0}, 0, WHITE);
        }
        else if (aIntro.key >= 190 && aIntro.key < 230)
        {
            DrawTexturePro(mUiTexture[4], {0, 0, 27, 27}, 
                {(float)GetScreenWidth()  / 2 - (float)256 / 2, 
                 (float)GetScreenHeight() / 2 - (float)256 / 2,
                 256, 256},
                {0, 0}, 0, WHITE);
        }
        else
        {
            DrawTexturePro(mUiTexture[5], {0, 0, 710, 200}, 
                {(float)GetScreenWidth()  / 2 - 355, 
                 (float)GetScreenHeight() / 2 - 100,
                 710, 200},
                {0, 0}, 0, WHITE);
        }
        aIntro.key++;
    }
    else
    {
        mSId = SceneId::MAIN_MENU;
    }
        
    // SFX played in this animation.
    if (aIntro.key == 120) PlaySoundMulti(mUiSfx[0]);
    if (aIntro.key == 160) PlaySoundMulti(mUiSfx[0]);
    if (aIntro.key == 180) PlaySoundMulti(mUiSfx[0]);
    if (aIntro.key == 190) PlaySoundMulti(mUiSfx[0]);
    if (aIntro.key == 230) PlaySoundMulti(mUiSfx[0]);
    if (aIntro.key == 250) PlaySoundMulti(mUiSfx[1]);
}

void Ui::DrawMainMenu()
{
    // Draw background and game logo.
    DrawTexturePro(mUiTexture[6], {0, 0, 1024, 768}, {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0, 0}, 0, WHITE);
    DrawTexturePro(mUiTexture[7], {0, 0, 400, 80}, {(float)GetScreenWidth() / 2 - 250, (float)GetScreenHeight() / 3 - 100, 500, 100}, {0, 0}, 0, WHITE);
    DrawTextPro(mUiFont, "Map Editor", 
               {(float)(GetScreenWidth() / 2) - (MeasureTextEx(mUiFont,"Map Editor",200,0).x / 2),
                (float)GetScreenHeight() / 3 - 300},
               {0, 0}, 0, 200, 0, RED);
    
    
    // Buttons creation.
    Button b_play(80, "Start Editor", WHITE, 
                 {(float)GetScreenWidth() /2 - 225,
                  (float)GetScreenHeight() / 3+100,
                  450  ,
                  100},
                 mUiTexture[8], mUiFont);

    Button b_quit(80, "QUIT", WHITE,
                   {(float)GetScreenWidth() /2 - 125,
                    (float)GetScreenHeight() / 3 + 250, 
                    250,
                    100},
                    mUiTexture[8], mUiFont);
    
    // Buttons draw.
    b_play.Draw(cState);
    b_quit.Draw(cState);

    // Buttons scripting.
    if (b_play.IsClicked(cState)) mSId              = SceneId::SELECT_MENU;
    if (b_quit.IsClicked(cState)) mGameRef.needStop = true;
}

void Ui::DrawEditorMenu()
{  
    // Draw background.
    DrawTexturePro(mUiTexture[6], {0, 0, 1024, 768}, {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0, 0}, 0, WHITE);

    // Draw menu buttons.
    Button widthPlus(80,   "+",     WHITE, {(float)GetScreenWidth() /2 - 425, (float)GetScreenHeight() / 3 + 50,  200, 100}, mUiTexture[8], mUiFont);
    Button widthMinus(80,  "-",     WHITE, {(float)GetScreenWidth() /2 + 225, (float)GetScreenHeight() / 3 + 50,  200, 100}, mUiTexture[8], mUiFont);
    Button heightPlus(80,  "+",     WHITE, {(float)GetScreenWidth() /2 - 425, (float)GetScreenHeight() / 3 + 300, 200, 100}, mUiTexture[8], mUiFont);
    Button heightMinus(80, "-",     WHITE, {(float)GetScreenWidth() /2 + 225, (float)GetScreenHeight() / 3 + 300, 200, 100}, mUiTexture[8], mUiFont);
    Button validate(80, "Validate", WHITE, {(float)GetScreenWidth() /2 - 225, (float)GetScreenHeight() / 3 + 500, 450, 100}, mUiTexture[8], mUiFont);

    widthMinus.Draw(cState);
    widthPlus.Draw(cState);
    heightMinus.Draw(cState);
    heightPlus.Draw(cState);

    if (widthPlus.IsClicked(cState))
    {
        fileData.width++;
        if(fileData.width > 40) fileData.width = 40;
    }
    if (widthMinus.IsClicked(cState))
    {
        fileData.width--;
        if(fileData.width < 14) fileData.width = 14;
    } 

    if (heightPlus.IsClicked(cState))
    {
        fileData.height++;
        if(fileData.height > 40) fileData.height = 40;
    }
    if (heightMinus.IsClicked(cState))
    {
        fileData.height--;
        if(fileData.height < 12) fileData.height = 12;
    }

    // Text box display.
    fileData.textBox.x      = (float)GetScreenWidth() /2 - 200;
    fileData.textBox.y      = (float)GetScreenHeight() /2 - 250;
    fileData.textBox.width  = 400;
    fileData.textBox.height = 80;

    DrawTextEx(mUiFont, "File Information", {(float)GetScreenWidth() / 2 - MeasureTextEx(mUiFont, "File Information", 100, 0).x / 2, 50}, 100, 0, WHITE);
    DrawText("File name:", (float)GetScreenWidth() /2 -200, (float)GetScreenHeight() /2 - 290, 30, WHITE);

    DrawRectangleRec(fileData.textBox, LIGHTGRAY);

    if (fileData.canWriteInBox) DrawRectangleLines((int)fileData.textBox.x, 
                                                   (int)fileData.textBox.y,
                                                   (int)fileData.textBox.width,
                                                   (int)fileData.textBox.height,
                                                   RED);

    else                        DrawRectangleLines((int)fileData.textBox.x,
                                                   (int)fileData.textBox.y,
                                                   (int)fileData.textBox.width,
                                                   (int)fileData.textBox.height,
                                                   DARKGRAY);

    DrawText(fileData.name, (int)fileData.textBox.x + 5, (int)fileData.textBox.y + 8, 65, MAROON);
    DrawText(TextFormat("%i/%i", fileData.letterCount, 9), (float)GetScreenWidth() /2 +215, (float)GetScreenHeight() /2 - 190, 25, GRAY);

    if (fileData.canWriteInBox && fileData.letterCount < 9)
        DrawText("|", (int)fileData.textBox.x + 8 + MeasureText(fileData.name, 65), (int)fileData.textBox.y + 12, 65, MAROON);
    
    // Text display.
    DrawText("Width:", GetScreenWidth() /2 - MeasureTextEx(GetFontDefault(), "Width", 35, 0).x/2, GetScreenHeight() / 3 + 25, 35, WHITE);
    DrawText(TextFormat("%d",fileData.width), GetScreenWidth() /2 - MeasureTextEx(GetFontDefault(), TextFormat("%d",fileData.width), 46, 0).x/2, GetScreenHeight() / 3+70, 46, WHITE);
    DrawText("Height:", GetScreenWidth() /2 - MeasureTextEx(GetFontDefault(), "Height", 35, 0).x/2, GetScreenHeight() / 3+280, 35, WHITE);
    DrawText(TextFormat("%d",fileData.height), GetScreenWidth() /2 - MeasureTextEx(GetFontDefault(), TextFormat("%d",fileData.height), 46, 0).x/2, GetScreenHeight() / 3+325, 46, WHITE);

    // Errors display.   
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
    
    // Text box update.
    if (CheckCollisionPointRec(GetMousePosition(), fileData.textBox) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) 
    {
        fileData.canWriteInBox = true;
    }
    else
    { 
        fileData.canWriteInBox = false;
    }

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

        if(validate.IsClicked(cState))
        {
            if (fileData.name[0]!='\0')
            {
                for (int i = 0; fileData.name[i]!='\0'; i++)
                {
                    if ((fileData.name[i] >= 48 && fileData.name[i] <= 57)||(fileData.name[i] >= 65 && fileData.name[i] <= 90)||(fileData.name[i] >= 97 && fileData.name[i] <= 122)||fileData.name[i] == 95)
                    {
                        fileData.saveTryIncorect =false;
                    }
                    else
                    {
                        fileData.saveTryIncorect =true;
                        break;
                    }
                    
                }
                if (!fileData.saveTryIncorect)
                {
                    
                    hasPutInformation=true;
                    
                }
                fileData.saveTryEmpty = false;
                
            }
            else
            {
                fileData.saveTryEmpty = true;
            }

        }

    if (hasPutInformation) mSId = SceneId::LOADING;  
}

void Ui::DrawInGame()
{
    if(!mUiHovered) mGameRef.mTm.Update(selectedTool, onRightClick, onLeftClick, mInGameCamera);
    mGameRef.mTm.Draw();
}

void Ui::DrawHUD()
{
    // Hide / show HUD bind.
    if (IsKeyPressed(KEY_LEFT_CONTROL))
    {
        if (mHudIsActive)
        {
            mHudIsActive = false;
            mUiHovered = false;
        }
        else
        {
            mHudIsActive = true;
        }
        
    }
    
    if (mHudIsActive)
    {
        TilePaint paint({0, (float)(GetScreenHeight() - (mUiTexture[15].height *1.5)), 128 * 1.5, 224 * 1.5},mUiTexture[15], 32);
        Button saver({0, 0, 50, 50}, mUiTexture[14]);
        Button eraser({0, 100, 50, 50},mUiTexture[12]);
        Button writer({0, 50, 50, 50},mUiTexture[13]);
        Button information({(float)GetScreenWidth() - 50, 0, 50, 50}, mUiTexture[18]);
        Button flag({0, 150, 50, 50}, mUiTexture[19]);
             

        // Update HUD buttons.
        if (writer.IsClicked(cState))      selectedTool = 1;
        else if (eraser.IsClicked(cState)) selectedTool = 2;
        else if(flag.IsClicked(cState))    selectedTool = 3;
            
        if (paint.IsRClicked(cState))
        {
            for (int i = 0; i < ((paint.tileTexture.width / paint.tilesize) * (paint.tileTexture.height / paint.tilesize)); i++)
                if(CheckCollisionPointRec(GetMousePosition(), paint.tileList[i])) 
                    onRightClick = i;
        }
        if (paint.IsLClicked(cState))
        {
            for (int i = 0; i<((paint.tileTexture.width / paint.tilesize) * (paint.tileTexture.height / paint.tilesize)); i++)
                if(CheckCollisionPointRec(GetMousePosition(), paint.tileList[i]))
                    onLeftClick = i;
        }
        
        if (paint.IsHovered(cState)      ||
            saver.IsHovered(cState)      ||
            writer.IsHovered(cState)     ||
            eraser.IsHovered(cState)     ||
            information.IsHovered(cState)||
            flag.IsHovered(cState))
        {
            mUiHovered = true;
        }
        else
        {
            mUiHovered = false;
        }

        if (information.IsHovered(cState))
        {
            Rectangle shortcutInformaton = {information.rec.x - 200,information.rec.y + 50, 200, 200};
            
            DrawRectangleRec(shortcutInformaton, {191, 191, 191, 255});
            DrawRectangleLinesEx(shortcutInformaton, 3, {75, 75, 75 ,255});
            DrawTextPro(GetFontDefault(),"Left Ctrl to hide HUD",
                        {shortcutInformaton.x + 15, shortcutInformaton.y + 15},
                        {0, 0}, 0, 17.5, 1, {75, 75, 75, 255});
            
        }

        if (saver.IsClicked(cState))
        {
            mGameRef.mTm.Save();
        }
        
        // Draw HUD.
        DrawTexturePro(paint.tileTexture, {paint.originalPostion[onRightClick].x, paint.originalPostion[onRightClick].y, 32, 32},
                                          {paint.rec.x + 50, paint.rec.y - 60, 50, 50}, {0, 0}, 0, WHITE);
        DrawRectangleLinesEx({paint.rec.x + 50, paint.rec.y - 60, 50, 50}, 3, DARKGRAY);
        DrawTexturePro(paint.tileTexture,{paint.originalPostion[onLeftClick].x, paint.originalPostion[onLeftClick].y, 32, 32},
                                         {paint.rec.x + 15, paint.rec.y - 80, 50, 50}, {0, 0}, 0, WHITE);
        DrawRectangleLinesEx({paint.rec.x + 15, paint.rec.y - 80, 50, 50}, 3, DARKGRAY); 

        paint.Draw(cState);
        saver.Draw(cState);
        writer.Draw(cState);
        eraser.Draw(cState);
        information.Draw(cState);
        flag.Draw(cState);

        // Draw active rectangle.
        switch(selectedTool)
        {
            case 1:
                DrawRectangleLinesEx(writer.rec, 4, RED);
                break;
            case 2:
                DrawRectangleLinesEx(eraser.rec, 4, RED);
                break;
            case 3:
                DrawRectangleLinesEx(flag.rec, 4, RED);
                break;
        }
    }
}

void Ui::DrawOverlay()
{
    // Draw scene according to the current scene ID.
   switch (mSId)
    {
    case SceneId::INTRO:
        DrawIntro();
        break;

    case SceneId::MAIN_MENU:
        DrawMainMenu();
        break;

    case SceneId::SELECT_MENU:
        DrawEditorMenu();
        break;

    case SceneId::IN_GAME:
        DrawHUD();
        break;
    
    default:
        break;
    }   

    // Draw cursor according to it state.
    DrawTextureEx(mUiTexture[9 + (int)cState], GetMousePosition(), 0, 3, WHITE);
}

void Ui::IsCameraOut()
{
    if (mInGameCamera.target.x < 0)
    {                                      
        mInGameCamera.target.x = 0;
        mIsCameraOut = true;
    }

    if (mInGameCamera.target.y < 0)
    {
        mInGameCamera.target.y = 0;
        mIsCameraOut = true;
    }

    if (mInGameCamera.target.x + GetScreenWidth() / mInGameCamera.zoom >
        mGameRef.mTm.mWidth * TILE_SIZE)
    {
        mInGameCamera.target.x = mGameRef.mTm.mWidth * TILE_SIZE -
                                 GetScreenWidth() / mInGameCamera.zoom;
        mIsCameraOut = true;
    }

    if (mInGameCamera.target.y + GetScreenHeight() / mInGameCamera.zoom >
        mGameRef.mTm.mHeight * TILE_SIZE)
    {
        mInGameCamera.target.y = mGameRef.mTm.mHeight * TILE_SIZE - 
                                 GetScreenHeight() / mInGameCamera.zoom;
        mIsCameraOut = true;
    }
    
    mIsCameraOut = false;
}

void Ui::Update()
{
    
    // Scenes update.
    switch (mSId)
    {
    case SceneId::LOADING:
        mGameRef.mTm.Init(fileData.width,fileData.height, mUiTexture->width, mUiTexture->height,fileData.name);
        mInGameCamera.zoom = 3.0f;
        break;

    case SceneId::IN_GAME:
        // Camera movements update.
        IsCameraOut();
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) && 
            !mIsCameraOut)
        {            
            mInGameCamera.target.x += -GetMouseDelta().x / mInGameCamera.zoom;
            mInGameCamera.target.y += -GetMouseDelta().y / mInGameCamera.zoom;
        }
        IsCameraOut();
        break;
    
    default:
        break;
    }       
     
}

void Ui::DrawRender()
{ 
    if (mSId == SceneId::IN_GAME) DrawInGame();
}
