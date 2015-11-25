#include "Hud.h"
#include <iostream>

Hud::Hud(SDL_Renderer *renderTarget, DrawContainer *dc, FPS *fpsCounter, int top, int left)
{
	this->fpsCounter = fpsCounter;

	skull = new HudObject( renderTarget, "Images/hud/skull.png" );
	
	healthbarOverlay = new HudObject( renderTarget, "Images/hud/healthbar.png" );
	terrorbarOverlay = new HudObject( renderTarget, "Images/hud/terrorbar.png" );
	
	health = 100;
	terror = 100;

	maxHealth = 100;
	maxTerror = 100;
	
	healthbarMax = 364;
	terrorbarMax = 312;
	healthbar = new Rect( left + 150, top + 33, (healthbarMax/maxHealth) * health, 25, 255, 0, 0, 255 );
	terrorbar = new Rect( left + 162, top + 76, (terrorbarMax/maxTerror) * terror, 16, 0, 91, 127, 255 );

	skull->positionRect.y = top;
	skull->positionRect.x = left;

	healthbarOverlay->positionRect.x = left + 88;
	healthbarOverlay->positionRect.y = top + 17;

	terrorbarOverlay->positionRect.x = left + 148;
	terrorbarOverlay->positionRect.y = top + 65;

	dc->add( terrorbar );
	dc->add( terrorbarOverlay );
	dc->add( healthbar );
	dc->add( healthbarOverlay );
	dc->add( skull );
}


Hud::~Hud()
{
	delete skull;				skull = nullptr;
	delete healthbarOverlay;	healthbarOverlay = nullptr;
	delete terrorbarOverlay;	terrorbarOverlay = nullptr;
	delete healthbar;			healthbar = nullptr;
	delete terrorbar;			terrorbar = nullptr;
}

//void Hud::accept( UpdateVisitor *uv, float deltaTime, const Uint8 *keyState )
//{
//	uv->visit( this, deltaTime, keyState );
//}

void Hud::update( float deltaTime, const Uint8 *keyState )
{
	std::cout << "Updating interface, this is not normal, should have been overriden!" << std::endl;
}