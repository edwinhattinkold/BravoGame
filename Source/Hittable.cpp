#include "Hittable.h"
#include <iostream>

Hittable::Hittable(int maxHealth)
{
	this->maxHealth = maxHealth;
	health = this->maxHealth;
	dead = false;

	maxHealthBar.h = 15;
	healthBar.h = maxHealthBar.h;
	takenDamageBar.h = maxHealthBar.h;
	healthBarOffset = 25;
}


Hittable::~Hittable()
{

}

void Hittable::drawHealthBar(SDL_Renderer* renderTarget, SDL_Rect* cameraRect, SDL_Rect positionRect)
{
	hostPositionRect = positionRect;
	maxHealthBar.w = positionRect.w * 0.70;
	int widthDifference = positionRect.w - maxHealthBar.w;
	maxHealthBar.x = positionRect.x - cameraRect->x + (widthDifference / 2);
	maxHealthBar.y = positionRect.y - cameraRect->y - healthBarOffset;

	float healthPercentage = float(health) / float(maxHealth);
	healthBar.w = maxHealthBar.w * healthPercentage;
	healthBar.x = maxHealthBar.x;
	healthBar.y = maxHealthBar.y;

	float takenDamagePercentage = float( takenDamage ) / float( maxHealth );
	takenDamageBar.w = maxHealthBar.w * takenDamagePercentage;
	takenDamageBar.x = healthBar.x + healthBar.w;
	takenDamageBar.y = maxHealthBar.y;

	SDL_SetRenderDrawColor( renderTarget, 255, 0, 0, 255 );
	SDL_RenderFillRect( renderTarget, &takenDamageBar );

	SDL_SetRenderDrawColor( renderTarget, 13, 127, 255, 255 );
	SDL_RenderFillRect( renderTarget, &healthBar );

	SDL_SetRenderDrawColor( renderTarget, 0, 0, 0, 255 );
	SDL_RenderDrawRect( renderTarget, &maxHealthBar );

	if( takenDamage <= 0 )
		takenDamage = 0;
	else
		takenDamage -= maxHealthBar.w * 0.05;

	int numberOfHundreds = health / 100;
	float onePixelValue = float(health) / float(healthBar.w);
	for( int c = 1; c < numberOfHundreds + 1; c++ )
	{
		int x1 = healthBar.x + (100 / onePixelValue * c);
		int x2 = x1;
		int y1 = healthBar.y;
		int y2 = healthBar.y + healthBar.h - 2;
		SDL_RenderDrawLine( renderTarget, x1, y1, x2, y2 );
	}
}

void Hittable::takeDamage( int damage )
{
	if( !dead )
	{
		health -= damage;
		takenDamage += damage;
		if( health <= 0 )
		{
			dead = true;
			health = 0;
		}
	}	
}

bool Hittable::isDead(){
	return dead;
}

SDL_Rect Hittable::getHostPosition()
{
	return hostPositionRect;
}