#include "Hud.h"

Hud::Hud( SDL_Renderer *renderTarget, DrawContainer *dc, FPS *fpsCounter, SDL_Window *window, Camera *camera,  int top, int left )
{
	this->renderTarget = renderTarget;
	this->fpsCounter = fpsCounter;
	this->top = top;
	this->left = left;
	this->window = window;
	this->camera = camera;

	this->font = TTF_OpenFont( "Fonts/28dayslater.ttf", 40 );

	health = 50;
	terror = 80;

	maxHealth = 100;
	maxTerror = 100;
	
	healthbarMax = 364;
	terrorbarMax = 312;

	skull = new HudObject( renderTarget, "Images/hud/skull.png" );
	
	healthbarOverlay = new HudObject( renderTarget, "Images/hud/healthbar.png" );
	terrorbarOverlay = new HudObject( renderTarget, "Images/hud/terrorbar.png" );
	
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
	
	fpsDisplay = new MenuItem( renderTarget, font, "0" );
	
	fpsDisplay->setXPosition( camera->windowWidth - left - 50 );
	fpsDisplay->setYPosition( top );

}


Hud::~Hud()
{
	delete skull;				skull = nullptr;
	delete healthbarOverlay;	healthbarOverlay = nullptr;
	delete terrorbarOverlay;	terrorbarOverlay = nullptr;
	delete healthbar;			healthbar = nullptr;
	delete terrorbar;			terrorbar = nullptr;
	delete fpsDisplay;			fpsDisplay = nullptr;
}


void Hud::draw( SDL_Renderer *renderTarget)
{
	
	fpsDisplay->setXPosition( camera->windowWidth - left - 100 );
	fpsDisplay->setYPosition( top );

	string s = to_string( fpsCounter->fps_current );
	char *text = (char*) s.c_str();
	fpsDisplay->setText( renderTarget, text);
	fpsDisplay->draw( renderTarget );
}

void Hud::accept( DrawVisitor *dv )
{
	dv->visit( this );
}