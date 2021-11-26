#include"draw.hpp"


void drawStart(common::Game &game);
void drawEditor(common::Game &game);

void draw::draw(common::Game &game){
    switch (game.gameState)
    {
    case 0:
        drawStart(game);
        break;
    case 1:
        drawEditor(game);
        break;
    
    default:
        break;
    }
    
}

void drawStart(common::Game &game){
    game.start.quit->update(game);
    game.start.start->update(game);
    if (game.start.start->isPressed)
    {
        game.gameState = 1;
    }
    
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("Map Maker",SCREEN_WIDTH-MeasureTextEx(GetFontDefault(),"Map Maker",100,5).x*2,30,150,RED);
    game.start.start->draw("Start Editor", SCREEN_WIDTH-MeasureTextEx(GetFontDefault(),"Start Editor",100,1.5).x*2, 300,80);
    game.start.quit->draw("QUIT", SCREEN_WIDTH-MeasureTextEx(GetFontDefault(),"QUIT",100,55).x*2, 600,80);
    EndDrawing();
}

void drawEditor(common::Game &game){
    //name
    if (CheckCollisionPointRec(GetMousePosition(), game.editor.fileInfo.textBox) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) game.editor.fileInfo.canWriteInBox = true;
    else if (!CheckCollisionPointRec(GetMousePosition(), game.editor.fileInfo.textBox) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) game.editor.fileInfo.canWriteInBox = false;
    if (game.editor.fileInfo.canWriteInBox)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (game.editor.fileInfo.letterCount < MAX_INPUT_CHARS))
            {
                game.editor.fileInfo.name[game.editor.fileInfo.letterCount] = (char)key;
                game.editor.fileInfo.name[game.editor.fileInfo.letterCount+1] = '\0'; // Add null terminator at the end of the string.
                game.editor.fileInfo.letterCount++;
            }

           key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            game.editor.fileInfo.letterCount--;
            if (game.editor.fileInfo.letterCount < 0) game.editor.fileInfo.letterCount = 0;
            game.editor.fileInfo.name[game.editor.fileInfo.letterCount] = '\0';
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (game.editor.fileInfo.heightPlus->isPressed)
    {
        game.editor.fileInfo.height++;
        if(game.editor.fileInfo.height>50) game.editor.fileInfo.height=50;
    }
    if (game.editor.fileInfo.heightMinus->isPressed)
    {
        game.editor.fileInfo.height--;
        if(game.editor.fileInfo.height<1) game.editor.fileInfo.height=1;
    }

    if (game.editor.fileInfo.widthPlus->isPressed)
    {
        game.editor.fileInfo.width++;
        if(game.editor.fileInfo.width>50) game.editor.fileInfo.width=50;
    }
    if (game.editor.fileInfo.widthMinus->isPressed)
    {
        game.editor.fileInfo.width--;
        if(game.editor.fileInfo.width<1) game.editor.fileInfo.width=1;
    }
    

    BeginDrawing();
    ClearBackground(RAYWHITE);

        DrawText("File name:", 50, 50, 20, GRAY);
        DrawRectangleRec(game.editor.fileInfo.textBox, LIGHTGRAY);
        if (game.editor.fileInfo.canWriteInBox) DrawRectangleLines((int)game.editor.fileInfo.textBox.x, (int)game.editor.fileInfo.textBox.y, (int)game.editor.fileInfo.textBox.width, (int)game.editor.fileInfo.textBox.height, RED);
        else DrawRectangleLines((int)game.editor.fileInfo.textBox.x, (int)game.editor.fileInfo.textBox.y, (int)game.editor.fileInfo.textBox.width, (int)game.editor.fileInfo.textBox.height, DARKGRAY);
        DrawText(game.editor.fileInfo.name, (int)game.editor.fileInfo.textBox.x + 5, (int)game.editor.fileInfo.textBox.y + 8, 40, MAROON);
        DrawText(TextFormat("%i/%i", game.editor.fileInfo.letterCount, MAX_INPUT_CHARS), 280, 110, 20, DARKGRAY);
        if (game.editor.fileInfo.canWriteInBox)
        {
            if (game.editor.fileInfo.letterCount < MAX_INPUT_CHARS)
            {
                // Draw blinking underscore char
                DrawText("_", (int)game.editor.fileInfo.textBox.x + 8 + MeasureText(game.editor.fileInfo.name, 40), (int)game.editor.fileInfo.textBox.y + 12, 40, MAROON);
            }
        }

        DrawText("Width:", 50, 140, 20, GRAY);
        game.editor.fileInfo.widthMinus->draw("-",50,170,26);
        game.editor.fileInfo.widthMinus->update(game);
        DrawText(TextFormat("%d",game.editor.fileInfo.width), 80, 170, 26, GRAY);
        game.editor.fileInfo.widthPlus->draw("+",110,170,26);
        game.editor.fileInfo.widthPlus->update(game);

        DrawText("Height:", 50, 230, 20, GRAY);
        game.editor.fileInfo.heightMinus->draw("-",50,260,26);
        game.editor.fileInfo.heightMinus->update(game);
        DrawText(TextFormat("%d",game.editor.fileInfo.height), 80, 260, 26, GRAY);
        game.editor.fileInfo.heightPlus->draw("+",110,260,26);
        game.editor.fileInfo.heightPlus->update(game);

    EndDrawing();
}