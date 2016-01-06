#ifndef SPRITE_H
#define SPRITE_H
#include "SDL.h"
#include <string>
#include <vector>
#include "IDrawable.h"
#include "IUpdateable.h"
#include "Animation.h"
#include "DrawContainer.h"
#include "UpdateContainer.h"
#include "Assets.h"

class Sprite : public IDrawable, public IUpdateable
{
private:
	const int scale = 20;
protected:
	std::vector<Animation*> *animations;
	int currentAnimation;
	int angle;
	Asset asset;
public:
	/* Inheritance constructor */
	Sprite(int xPosition, int yPosition);

	/* Car constructor */
	Sprite(SDL_Renderer* renderTarget, Asset asset);

	/* Default constructor */
	Sprite(SDL_Renderer *renderTarget, Asset asset, int xPosition, int yPosition, int framesX, int framesY, float animationSpeed);

	~Sprite();

	virtual void updateAnimation(float delta);
	virtual void draw(SDL_Renderer *renderTarget, SDL_Rect camerRect);
	virtual void draw( SDL_Renderer *renderTarget );
	virtual void drawTree(SDL_Renderer *renderTarget, SDL_Rect camerRect);
	virtual void drawCollidable(SDL_Renderer *renderTarget, SDL_Rect camerRect);
	virtual void drawWithAngle(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	virtual void drawCar(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	virtual void drawTire(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	virtual void drawProjectile( SDL_Renderer *renderTarget, SDL_Rect cameraRect );
	virtual void drawCollectible(SDL_Renderer *renderTarget, SDL_Rect camerRect);
	bool intersectsWith(Sprite &p);

	SDL_Rect positionRect;

	int getPositionX();
	int getPositionY();

	void setOriginX(int newOriginX);
	void setOriginY(int newOriginY);
	void updateSDLPosition(float, float, float, float, float);

	int getOriginX();
	int getOriginY();
	void updateOrigin();
	void setAsset(Asset asset);
	Asset getAsset();

	bool animationDone();
};

#endif

