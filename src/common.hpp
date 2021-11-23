#pragma once
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

#include <raylib.h>
#include <string>

#include"utils.hpp"



namespace common{
	
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
        Color color = BLACK;
    public:
		Texture2D	buttonTexture;
    	Rectangle   sizeOfFrame;
        void draw(std::string text, int x, int y,int size);
        void update(common::Game &game);
    };

	class StartScreen
	{
	public:
		Button* bu;
	};
	class Game{
	public:
		int gameState; // 0: Start; 1: Parameter; 2: editor
		StartScreen start;
	};


}