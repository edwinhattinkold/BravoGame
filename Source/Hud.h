#pragma once
#include "HudObject.h"
#include "Rect.h"
#include "FPS.h"
class Hud
	: public IUpdateable
{
private:
	HudObject *skull;
	HudObject *healthbarOverlay;
	HudObject *terrorbarOverlay;
	Rect *healthbar;
	Rect *terrorbar;
	float health; //This should be a reference to the player (or object containing health and terror)
	float terror;
	float maxHealth;
	float maxTerror;
	float healthbarMax;
	float terrorbarMax;
	
	FPS *fpsCounter;

public:
	Hud( SDL_Renderer *renderTarget, DrawContainer *dc, FPS *fpsCounter, int top = 24, int left = 24 );
	~Hud();
	virtual void update( float delta, const Uint8 *keyState);
};

