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

	hud = new HudObject( renderTarget, Asset_HUD );
	
	healthbar = new Rect( left + 150, top + 33, (healthbarMax/maxHealth) * health, 25, 255, 0, 0, 255 );
	terrorbar = new Rect( left + 162, top + 76, (terrorbarMax/maxTerror) * terror, 16, 0, 91, 127, 255 );

	hud->positionRect.y = top;
	hud->positionRect.x = left;

	dc->add( terrorbar );
	dc->add( healthbar );
	dc->add( hud );
	
	fpsDisplay = new MenuItem( renderTarget, font, "0" );
	
	fpsDisplay->setXPosition( camera->windowWidth - left - 50 );
	fpsDisplay->setYPosition( top );

}


Hud::~Hud()
{
	delete hud;					hud = nullptr;
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