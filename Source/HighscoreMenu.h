#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "SDL.h"
#include "Camera.h"
#include "MenuItem.h"
#include "Assets.h"
using namespace std;
class HighscoreMenu
{
private:
	static enum Choices
	{
		Back
	};

	SDL_Texture *background;
	MenuItem *backButton;
	Camera *camera;
	vector<pair<string, string>> *highscores;

	void tick( SDL_Renderer *renderTarget );
	void removeMenu();

public:
	HighscoreMenu( SDL_Renderer *renderTarget, Camera* camera, TTF_Font* font );
	~HighscoreMenu();

	void showMenu( SDL_Renderer *renderTarget );
	void loadHighScores();
	static bool sortScores( pair<string, string> score1, pair<string, string> score2 );
	
};

