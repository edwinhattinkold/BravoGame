#pragma once
#include <SDL_ttf.h>
#include <string>
#include "HudObject.h"
#include "Rect.h"
#include "FPS.h"
#include "MenuItem.h"
#include "Camera.h"

using namespace std;
class Hud
	: public IDrawable
{
private:
	HudObject *hud;
	Rect *healthbar;
	Rect *terrorbar;
	float health; //This should be a reference to the player (or object containing health and terror)
	float terror;
	float maxHealth;
	float maxTerror;
	float healthbarMax;
	float terrorbarMax;
	float scale;

	int top;
	int left;
	
	SDL_Renderer *renderTarget;
	SDL_Window *window;
	FPS *fpsCounter;
	TTF_Font* font;
	MenuItem *fpsDisplay;
	Camera *camera;

public:
	Hud( SDL_Renderer *renderTarget, DrawContainer *dc, FPS *fpsCounter, SDL_Window *window, Camera *camera, int top = 24, int left = 24, float scale = 0.8 );
	~Hud();
	virtual void accept( DrawVisitor *dv );
	virtual void draw( SDL_Renderer *renderTarget );
};

