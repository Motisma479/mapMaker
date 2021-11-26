#include "utils.hpp"
void common::Button::draw(std::string text, int x, int y,int size){
        sizeOfInteraction.x=x;
        sizeOfInteraction.y=y;
        sizeOfInteraction.height= size*1.5;
        sizeOfInteraction.width=(float) size*text.length();
        DrawText(text.c_str()   
                ,x+sizeOfInteraction.width/2.5 - MeasureTextEx(GetFontDefault(),text.c_str(),size,0).x/2.5
                ,y+sizeOfInteraction.height/4.5
                ,size,color); 
        DrawRectangleLinesEx(sizeOfInteraction,size/10,color);
        
}
void common::Button::update(common::Game &game){
    if (CheckCollisionPointRec(game.mousePoint, sizeOfInteraction))
    {
        
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            color = (Color){ 93, 83, 26, 255 };
        }
        else{
            color = (Color){ 230, 202, 41, 255 };
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            isPressed = true;
        }else{
            isPressed = false;
        }
    }else{
        color= BLACK;
    }

  
}