#include "Camera.h"
#include <iostream>


Camera::Camera( int levelWidth, int levelHeight, int windowWidth, int windowHeight )
{
	this->levelWidth = levelWidth;
	this->levelHeight = levelHeight;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	cameraRect = new SDL_Rect();
	cameraRect->w = windowWidth;
	cameraRect->h = windowHeight;
	cameraRect->x = 0;
	cameraRect->y = 0;
	cameraShakeTime = 0;
	shakeMagnitude = 0;
}


Camera::~Camera( void )
{
	delete cameraRect;	cameraRect = nullptr;
}

void Camera::update( int xPosition, int yPosition, float deltaTime )
{
	//std::cout << xPosition << " - " << yPosition << std::endl;
	cameraRect->x = xPosition - ( windowWidth / 2 );
	cameraRect->y = yPosition - ( windowHeight / 2 );
	if( cameraShakeTime > 0.00f )
	{
		cameraShakeTime -= deltaTime;
		cameraRect->x += Random::getInstance().nextInt( shakeMagnitude * -1, shakeMagnitude );
		cameraRect->y += Random::getInstance().nextInt( shakeMagnitude * -1, shakeMagnitude );
	}
}

SDL_Rect* Camera::getCamera()
{
	return cameraRect;
}

void Camera::cameraShake(float time, int magnitude)
{
	cameraShakeTime = time;
	shakeMagnitude = magnitude;
}