#include "Hud.h"

Hud::Hud( World *world, SDL_Renderer *renderTarget, DrawContainer *dc, FPS *fpsCounter, Camera *camera, TDCar *car,  int top, int left, float scale )
{
	this->scale = scale;
	this->renderTarget = renderTarget;
	this->fpsCounter = fpsCounter;
	this->top = top * scale;
	this->left = left * scale;
	this->camera = camera;
	this->car = car;
	this->world = world;

	this->font = TTF_OpenFont( "Fonts/28dayslater.ttf", 40 * scale );

	distance = 0;
	unitVector = pair<int, int>( 0, 0 );
	
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
	levelDisplay = new MenuItem( renderTarget, font, "" );

	fpsDisplay->setXPosition( camera->windowWidth - left - ( 50) );
	fpsDisplay->setYPosition( top );
	
	levelDisplay->setXPosition( camera->windowWidth / 2 );
	levelDisplay->setYPosition( camera->windowHeight / 2 - 200 );

	scoreDisplay->setXPosition( ( camera->windowWidth / 2 ) - ( scoreDisplay->getWidth() / 2 ) );
	scoreDisplay->setYPosition( top );

	missionDisplay->setXPosition( left );
	missionDisplay->setYPosition( top + 200 );
	objectiveDisplay->setXPosition( left );
	objectiveDisplay->setYPosition( top + 230 );

	closestObjective = nullptr;
	objectiveArrow = new Sprite( renderTarget, Asset_Menu_Arrow );
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
	delete levelDisplay;		levelDisplay = nullptr;
	delete objectiveArrow;		objectiveArrow = nullptr;
}

void Hud::changeLevel(string name)
{
	level = name;
	levelDisplay->setYPosition( camera->windowHeight / 2 - 200 );
}


void Hud::draw( SDL_Renderer *renderTarget)
{
	
	fpsDisplay->setXPosition( camera->windowWidth - left - ( 100));
	scoreDisplay->setXPosition( (camera->windowWidth/2) - (scoreDisplay->getWidth()/2) );
	levelDisplay->setXPosition( (camera->windowWidth / 2) - (levelDisplay->getWidth() / 2) );
	levelDisplay->setYPosition( levelDisplay->getYPosition() - 2 );

	string fps = to_string( fpsCounter->fps_current );
	string score = to_string( car->getScore() );
	
	fpsDisplay->setText( renderTarget, fps );
	fpsDisplay->draw( renderTarget );
	scoreDisplay->setText( renderTarget, score );
	scoreDisplay->draw( renderTarget );

	MissionControl& mc = MissionControl::getInstance();
	missionDisplay->setText( renderTarget, mc.getCurrentMissionTitle() );
	missionDisplay->draw( renderTarget );

	levelDisplay->setText(renderTarget, level );
	levelDisplay->draw( renderTarget );

	objectiveDisplay->setText( renderTarget, mc.getCurrentObjectiveTitle() + " " + mc.getCurrentObjectiveProgress() );
	objectiveDisplay->draw(renderTarget);

	float newHealth = ( healthbarMax / car->maxHealth ) * car->health;
	renderHealth( newHealth );

	if( closestObjective != nullptr )
	{
		//hier was ik gebleven
	}
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

void Hud::calcUnitVector()
{
	if( closestObjective != nullptr )
	{
		int i = pow( closestObjective->x - car->x, 2 );
		int j = pow( closestObjective->y - car->y, 2 );
	
		distance = sqrt(i + j);
		unitVector = pair<int, int>( i / distance, j / distance );
		angle = atan2( unitVector.second, unitVector.first ) * 180 / M_PI;
	}
}

IObjective* Hud::getClosestObjective()
{
	int thedistance = INT_MAX;
	IObjective* theObjective;
	vector<IObjective*> objectives = world->getObjectives();
	if( objectives.size() < 1 )
	{
		closestObjective = nullptr;
	} else
	{
		for( size_t i = 0; i < objectives.size(); i++ )
		{
			int ii = pow( objectives.at(i)->x - car->x, 2 );
			int j = pow( objectives.at( i )->y - car->y, 2 );

			int newDistance = sqrt( i + j );
			if( newDistance < thedistance )
			{
				closestObjective = objectives.at( i );
				thedistance = newDistance;
			}
		}
	}
	return closestObjective;
}