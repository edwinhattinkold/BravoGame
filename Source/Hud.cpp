#include "Hud.h"

Hud::Hud( SDL_Renderer *renderTarget, DrawContainer *dc, FPS *fpsCounter, SDL_Window *window, Camera *camera,  int top, int left, float scale )
{
	this->scale = scale;
	this->renderTarget = renderTarget;
	this->fpsCounter = fpsCounter;
	this->top = top * scale;
	this->left = left * scale;
	this->window = window;
	this->camera = camera;

	this->font = TTF_OpenFont( "Fonts/28dayslater.ttf", 40 * scale );

	health = 50;
	terror = 80;

	maxHealth = 100;
	maxTerror = 100;
	
	healthbarMax = 364 * scale;
	terrorbarMax = 312 * scale;

	hud = new HudObject( renderTarget, Asset_HUD );

	hud->positionRect.h = hud->positionRect.h * scale;
	hud->positionRect.w = hud->positionRect.w * scale;
	
	healthbar = new Rect( left + ( 150 * scale ), top + ( 33 * scale ), ( healthbarMax / maxHealth ) * health, 26 * scale, 255, 0, 0, 255 );
	terrorbar = new Rect( left + ( 162 * scale ), top + ( 76 * scale ), ( terrorbarMax / maxTerror ) * terror, 16 * scale, 0, 91, 127, 255 );

	hud->positionRect.y = top;
	hud->positionRect.x = left;

	dc->add( terrorbar );
	dc->add( healthbar );
	dc->add( hud );
	
	fpsDisplay = new MenuItem( renderTarget, font, "0" );
	
	fpsDisplay->setXPosition( camera->windowWidth - left - ( 50) );
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
	
	fpsDisplay->setXPosition( camera->windowWidth - left - ( 100));
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