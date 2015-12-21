#pragma once
#include "SDL.h"
class Hittable
{
private:
	int healthBarOffset;
protected:
	SDL_Rect maxHealthBar;
	SDL_Rect healthBar;
	SDL_Rect takenDamageBar;
	SDL_Rect hostPositionRect;
public:
	int maxHealth;
	int health;
	bool dead;
	int takenDamage;
	Hittable(int maxHealth);
	~Hittable();
	virtual void drawHealthBar( SDL_Renderer* renderTarget, SDL_Rect* cameraRect, SDL_Rect positionRect );
	virtual void takeDamage( int damage );
	bool isDead();
	SDL_Rect getHostPosition();
};

