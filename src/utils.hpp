#pragma once
#include "common.hpp"

namespace utils{
    class Clickable
    {
    public:
    Rectangle   sizeOfInteraction;
    bool	 	playerIsOn = false;
    Vector2 	position;
    };

    class Button : Clickable
    {
    protected:
        Color color;
    public:
		Texture2D	buttonTexture;
    	Rectangle   sizeOfFrame;
        void draw(std::string text, int x, int y,int size);
        void update();
    };
}