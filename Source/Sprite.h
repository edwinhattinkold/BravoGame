#ifndef SPRITE_H
#define SPRITE_H
#include "SDL.h"
#include <string>
#include <vector>
#include "Animation.h"

class Sprite
{
protected:
	std::vector<Animation*> animations;
	int currentAnimaton;
	int originX, originY;

public:
	/* Inheritance constructor */
	Sprite(int xPosition, int yPosition);

	/* Default constructor */
	Sprite(SDL_Renderer *renderTarget, std::string filePath, int xPosition, int yPosition, int framesX, int framesY, float animationSpeed);

	~Sprite();

	virtual void Update(float delta, const Uint8 *keyState);
	virtual void Draw(SDL_Renderer *renderTarget, SDL_Rect camerRect);
	bool IntersectsWith(Sprite &p);

	SDL_Rect positionRect;

	int getPositionX();
	int getPositionY();

	void setOriginX(int newOriginX);
	void setOriginY(int newOriginY);
};

#endif

