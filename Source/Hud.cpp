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

	
	terror = 20;
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
	missionDisplay = new MenuItem( renderTarget, font, "No mission currently" );
	objectiveDisplay = new MenuItem( renderTarget, font, "No objective currently" );

	fpsDisplay->setXPosition( camera->windowWidth - left - ( 50) );
	fpsDisplay->setYPosition( top );

	scoreDisplay->setXPosition( ( camera->windowWidth / 2 ) - ( scoreDisplay->getWidth() / 2 ) );
	scoreDisplay->setYPosition( top );

	missionDisplay->setXPosition( left );
	missionDisplay->setYPosition( top + 200 );
	objectiveDisplay->setXPosition( left );
	objectiveDisplay->setYPosition( top + 230 );

}


Hud::~Hud()
{
	delete hud;					hud = nullptr;
	delete healthbar;			healthbar = nullptr;
	delete terrorbar;			terrorbar = nullptr;
	delete slidingbar;			slidingbar = nullptr;
	delete fpsDisplay;			fpsDisplay = nullptr;
	delete scoreDisplay;		scoreDisplay = nullptr;
	delete missionDisplay;		missionDisplay = nullptr;
	delete objectiveDisplay;	objectiveDisplay = nullptr;
}


void Hud::draw( SDL_Renderer *renderTarget)
{
	
	fpsDisplay->setXPosition( camera->windowWidth - left - ( 100));
	scoreDisplay->setXPosition( (camera->windowWidth/2) - (scoreDisplay->getWidth()/2) );

	string fps = to_string( fpsCounter->fps_current );
	string score = to_string( car->getScore() );
	
	fpsDisplay->setText( renderTarget, fps );
	fpsDisplay->draw( renderTarget );
	scoreDisplay->setText( renderTarget, score );
	scoreDisplay->draw( renderTarget );

	MissionControl& mc = MissionControl::getInstance();
	missionDisplay->setText( renderTarget, mc.getCurrentMissionTitle() );
	missionDisplay->draw( renderTarget );

	objectiveDisplay->setText( renderTarget, mc.getCurrentObjectiveTitle() + " " + mc.getCurrentObjectiveProgress() );
	objectiveDisplay->draw(renderTarget);

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
	
	terrorbar->rect->w = (terrorbarMax / maxTerror) *  car->getGasoline();
	healthbar->rect->w = healthWidth;
	slidingbar->rect->w = slidingWidth;
}

void Hud::accept( DrawVisitor *dv )
{
	dv->visit( this );
}