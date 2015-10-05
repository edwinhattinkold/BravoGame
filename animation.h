#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Animation
{
private:
	SDL_Rect cropRect;
	SDL_Texture *texture;
	float frameCounter, animationSpeed;
	int frameWidth, frameHeight;
	int textureWidth, textureHeight;
	int startFrameX, startFrameY;

public:
	Animation(SDL_Renderer* renderTarget, std::string filePath, int framesX, int framesY, int startFrameX, int startFrameY, float animationSpeed);
	~Animation();
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderTarget, SDL_Rect drawingRect);
	void StandStill();

	int getOriginX();
	int getOriginY();
	int getFrameWidth();
	int getFrameHeight();
};

#endif

