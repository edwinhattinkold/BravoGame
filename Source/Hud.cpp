#include "Hud.h"

Hud::Hud( SDL_Renderer *renderTarget, DrawContainer *dc, FPS *fpsCounter, Camera *camera, TDCar *car,  int top, int left, float scale )
{
	this->scale = scale;
	this->renderTarget = renderTarget;
	this->fpsCounter = fpsCounter;
	this->top = top * scale;
	this->left = left * scale;
	this->camera = camera;
	this->car = car;

	this->font = TTF_OpenFont( "Fonts/28dayslater.ttf", 40 * scale );

	
	terror = 80;
	maxTerror = 100;
	
	healthbarMax = 364 * scale;
	terrorbarMax = 312 * scale;

	hud = new HudObject( renderTarget, Asset_HUD );

	hud->positionRect.h = hud->positionRect.h * scale;
	hud->positionRect.w = hud->positionRect.w * scale;

	healthWidth = ( healthbarMax / car->maxHealth ) * car->health;
	slidingWidth = healthWidth;
	
	healthbar = new Rect( left + ( 150 * scale ), top + ( 33 * scale ), healthWidth, 26 * scale, 255, 0, 0, 255 );
	slidingbar = new Rect( left + ( 150 * scale ), top + ( 33 * scale ), slidingWidth, 26 * scale, 255, 240, 0, 255 );
	terrorbar = new Rect( left + ( 162 * scale ), top + ( 76 * scale ), ( terrorbarMax / maxTerror ) * terror, 16 * scale, 0, 91, 127, 255 );

	hud->positionRect.y = top;
	hud->positionRect.x = left;

	dc->add( terrorbar );
	dc->add(slidingbar);
	dc->add( healthbar );
	dc->add( hud );
	
	fpsDisplay = new MenuItem( renderTarget, font, "0" );
	scoreDisplay = new MenuItem( renderTarget, font, "0" );

	fpsDisplay->setXPosition( camera->windowWidth - left - ( 50) );
	fpsDisplay->setYPosition( top );

	scoreDisplay->setXPosition( ( camera->windowWidth / 2 ) - ( scoreDisplay->getWidth() / 2 ) );
	scoreDisplay->setYPosition( top );

}


Hud::~Hud()
{
	delete hud;					hud = nullptr;
	delete healthbar;			healthbar = nullptr;
	delete terrorbar;			terrorbar = nullptr;
	delete slidingbar;			slidingbar = nullptr;
	delete fpsDisplay;			fpsDisplay = nullptr;
}


void Hud::draw( SDL_Renderer *renderTarget)
{
	
	fpsDisplay->setXPosition( camera->windowWidth - left - ( 100));
	fpsDisplay->setYPosition( top );

	scoreDisplay->setXPosition( (camera->windowWidth/2) - (scoreDisplay->getWidth()/2) );
	scoreDisplay->setYPosition( top );

	string s = to_string( fpsCounter->fps_current );
	char *fps = (char*) s.c_str();

	string sc = to_string( car->getScore() );
	char *score = (char*) sc.c_str();
	fpsDisplay->setText( renderTarget, fps );
	fpsDisplay->draw( renderTarget );
	scoreDisplay->setText( renderTarget, score );
	scoreDisplay->draw( renderTarget );

	float newHealth = ( healthbarMax / car->maxHealth ) * car->health;
	renderHealth( newHealth );
}

void Hud::renderHealth( float newHealth )
{
	if( healthWidth > newHealth )
	{
		healthWidth -= 2 * scale;
	} else if( healthWidth < newHealth )
	{
		healthWidth += 2 * scale;
	}
	if( abs( healthWidth - newHealth ) < 3 * scale )
	{
		healthWidth = newHealth;
	}

	if( slidingWidth > healthWidth )
	{
		slidingWidth -= 0.8 * scale;
	} else if( slidingWidth < healthWidth )
	{
		slidingWidth = healthWidth;
	}

	healthbar->rect->w = healthWidth;
	slidingbar->rect->w = slidingWidth;
}

void Hud::accept( DrawVisitor *dv )
{
	dv->visit( this );
}