#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Camera.h"
#include "MenuItem.h"
#include "Assets.h"
#include "Sound.h"
#include "World.h"
#include "Sprite.h"
#include <ctime>

using namespace std;
class HighscoreMenu
{
private:
	SDL_Renderer* renderTarget;
	Camera* camera;
	TTF_Font* font;
	TTF_Font* bigFont;
	World* world;
	Sound* sound;
	std::vector<MenuItem*>* menuItems;
	MenuItem *backButton;
	bool isSelected;
	int combinedHeight;
	int margin;
	int selected;
	vector<pair<string, string>> *highscores;

	SDL_Texture* backgroundImage;
	SDL_Rect backgroundImageRect;

	enum Choices
	{
		Main_Menu
	}; 


	void center();

public:
	HighscoreMenu( World* world, SDL_Renderer *renderTarget, Camera* camera);
	~HighscoreMenu();
	void tick( int mouseX, int mouseY );
	void handleKeyboardInput( SDL_Keycode keyPressed );
	void mouseButtonClicked( int mouseX, int mouseY );
	void handleChoice( int index );
	void firstTick();
	void loadHighScores();
	static bool sortScores( pair<string, string> score1, pair<string, string> score2 );

	string getNow();
};

