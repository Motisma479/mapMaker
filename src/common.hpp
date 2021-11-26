#pragma once
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960
#define MAX_INPUT_CHARS     9

#include <raylib.h>
#include <string>
#include <iostream>
#include"utils.hpp"

namespace common{
	class Game;
	
    class Button
    {
	protected:
        Color color = BLACK;
    public:
		Texture2D	buttonTexture;
    	Rectangle   sizeOfFrame;
		
		Rectangle   sizeOfInteraction;
		bool	 	playerIsOn = false;
		
		Vector2 	position;
		bool   		isPressed = false;

        void draw(std::string text, int x, int y,int size);
        void update(common::Game &game);
    };

	class StartScreen
	{
	public:
		Button* quit;
		Button* start;
	};

	class FileInformation{
	public:
		Rectangle textBox = { 50, 80, 225, 50 };
		bool canWriteInBox = false;
		char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    	int letterCount = 0;

		int width = 10;
		Button* widthPlus;
		Button* widthMinus;
		int height = 10;
		Button* heightPlus;
		Button* heightMinus;

	};

	class Editor{
	public:
		bool hasPutInformation = false;
		FileInformation fileInfo;
	};

	class Game{
	public:
		int gameState; // 0: Start; 1: Editor; 2: Parameter;  
		StartScreen start;
		Editor editor;
		Vector2 mousePoint = { 0.0f, 0.0f };
	};


}