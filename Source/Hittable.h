#pragma once
#include "SDL.h"
class Hittable
{
protected:
	int maxHealth;
	int health;
	int takenDamage;
	bool dead;
	SDL_Rect maxHealthBar;
	SDL_Rect healthBar;
	SDL_Rect takenDamageBar;
public:
	Hittable(int maxHealth);
	~Hittable();
	virtual void drawHealthBar( SDL_Renderer* renderTarget, SDL_Rect* cameraRect, SDL_Rect positionRect );
	virtual void takeDamage( int damage );
};
