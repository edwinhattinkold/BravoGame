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
}


Camera::~Camera( void )
{
	delete cameraRect;	cameraRect = nullptr;
}

void Camera::update( int xPosition, int yPosition )
{
	cameraRect->x = xPosition - ( windowWidth / 2 );
	cameraRect->y = yPosition - ( windowHeight / 2 );

	/*if( cameraRect->x < 0 )
		cameraRect->x = 0;
	if( cameraRect->y < 0 )
		cameraRect->y = 0;*/

	/*if( cameraRect->x + cameraRect->w >= levelWidth )
	{
		cameraRect->x = levelWidth - windowWidth;
	}
	if( cameraRect->y + cameraRect->h >= levelHeight )
		cameraRect->y = levelHeight - windowHeight;*/
}

SDL_Rect* Camera::getCamera()
{
	return cameraRect;
}