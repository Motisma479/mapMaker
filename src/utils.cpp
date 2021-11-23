#include "utils.hpp"
void common::Button::draw(std::string text, int x, int y,int size){
        
        DrawText(text.c_str(),x,y,size,color);
}
void common::Button::update(common::Game &game){
        
    color= RED;
}