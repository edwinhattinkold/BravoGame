#ifndef SPRITE_H
#define SPRITE_H
#include "SDL.h"
#include <string>
#include <vector>
#include "IDrawable.h"
#include "IUpdateable.h"
#include "Animation.h"
#include "DrawContainer.h"

class Sprite : public IDrawable, public IUpdateable
{
private:
	const int scale = 20;
protected:
	std::vector<Animation*> *animations;
	int currentAnimation;
	int angle;

public:
	/* Inheritance constructor */
	Sprite(int xPosition, int yPosition);

	/* Car constructor */
	Sprite(SDL_Renderer* renderTarget, std::string filePath);

	/* Default constructor */
	Sprite(SDL_Renderer *renderTarget, std::string filePath, int xPosition, int yPosition, int framesX, int framesY, float animationSpeed);

	~Sprite();

	virtual void update(float delta, const Uint8 *keyState);
	virtual void draw(SDL_Renderer *renderTarget, SDL_Rect camerRect);
	virtual void drawTree(SDL_Renderer *renderTarget, SDL_Rect camerRect);
	virtual void drawCar(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	bool intersectsWith(Sprite &p);

	SDL_Rect positionRect;

	int getPositionX();
	int getPositionY();

	void updateSDLPosition(int, int, int, int, float);
	void updateSDLPosition(float, float);

	int getOriginX();
	int getOriginY();
	void updateOrigin();
	void subscribe();
};

#endif

