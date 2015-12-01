#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include "SDL.h"
#include <string>
#include "Assets.h"

class Animation
{
private:
	SDL_Rect cropRect;
	SDL_Texture *texture;
	float frameCounter, animationSpeed;
	int frameWidth, frameHeight;
	int textureWidth, textureHeight;
	int startFrameX, startFrameY;
	int originX, originY;
public:
	Animation(SDL_Renderer* renderTarget, Asset asset, int framesX, int framesY, int startFrameX, int startFrameY, float animationSpeed);
	~Animation();
	void init(int framesY, int framesX);

	void update(float deltaTime);
	void draw(SDL_Renderer* renderTarget, SDL_Rect drawingRect);
	void drawTree(SDL_Renderer* renderTarget, SDL_Rect drawingRect, int angle);
	void drawCar(SDL_Renderer* renderTarget, SDL_Rect drawingRect, int angle);
	void DrawWithAngle(SDL_Renderer* renderTarget, SDL_Rect drawingRect, int angle);
	void standStill();

	int getOriginX();
	int getOriginY();
	void setOriginX(int newOriginX);
	void setOriginY(int newOriginY);
	void setAsset( Asset asset );
	int getFrameWidth();
	int getFrameHeight();

	bool done;
};

#endif

