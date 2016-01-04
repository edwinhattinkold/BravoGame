#pragma once
#include <SDL_ttf.h>
#include <string>
#include "HudObject.h"
#include "Rect.h"
#include "FPS.h"
#include "MenuItem.h"
#include "Camera.h"
#include "TDCar.h"

using namespace std;
class Hud
	: public IDrawable
{
private:
	HudObject *hud;
	
	Rect *healthbar;
	Rect *terrorbar;
	Rect *slidingbar;

	float terror;
	float maxTerror;
	float healthbarMax;
	float terrorbarMax;
	float scale;

	float healthWidth;
	float slidingWidth;

	int top;
	int left;
	
	SDL_Renderer *renderTarget;
	SDL_Window *window;
	FPS *fpsCounter;
	TTF_Font* font;
	
	MenuItem *fpsDisplay;
	MenuItem *scoreDisplay;
	MenuItem *levelDisplay;
	MenuItem *missionDisplay;
	MenuItem *objectiveDisplay;
	string level;
	Camera *camera;
	TDCar *car;
	void renderHealth( float newHealth );
	void renderTerror( float newTerror );

public:
	Hud( SDL_Renderer *renderTarget, DrawContainer *dc, FPS *fpsCounter, Camera *camera, TDCar *car, int top = 24, int left = 24, float scale = 0.8 );
	~Hud();
	virtual void accept( DrawVisitor *dv );
	virtual void draw( SDL_Renderer *renderTarget );
	void changeLevel( string name );
};

