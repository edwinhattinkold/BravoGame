#pragma once
#include "SDL.h"
class Hittable
{
private:
	int healthBarOffset;
protected:
	int maxHealth;
	int health;
	int takenDamage;
	bool dead;
	SDL_Rect maxHealthBar;
	SDL_Rect healthBar;
	SDL_Rect takenDamageBar;
	SDL_Rect hostPositionRect;
public:
	Hittable(int maxHealth);
	~Hittable();
	virtual void drawHealthBar( SDL_Renderer* renderTarget, SDL_Rect* cameraRect, SDL_Rect positionRect );
	virtual void takeDamage( int damage );
	bool isDead();
	SDL_Rect getHostPosition();
};

