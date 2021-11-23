#include"draw.hpp"

void draw::draw(common::Game &game){
    game.start.bu->update(game);
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("Map Maker",30,30,100,RED);
    game.start.bu->draw("TEST", 30, 150,80);
    EndDrawing();
}
