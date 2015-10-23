#include "Camera.h"
#include <iostream>


Camera::Camera(int levelWidth, int levelHeight, int windowWidth, int windowHeight)
{
	this->levelWidth = levelWidth;
	this->levelHeight = levelHeight;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->cameraRect = new SDL_Rect();
	this->cameraRect->w = this->windowWidth;
	this->cameraRect->h = this->windowHeight;
	this->cameraRect->x = 0;
	this->cameraRect->y = 0;
}


Camera::~Camera(void)
{

}

void Camera::Update(int xPosition, int yPosition){
	this->cameraRect->x = xPosition - (this->windowWidth / 2);
	this->cameraRect->y = yPosition - (this->windowHeight / 2);

	if (this->cameraRect->x < 0)
		this->cameraRect->x = 0;
	if (this->cameraRect->y < 0)
		this->cameraRect->y = 0;

	if (this->cameraRect->x + this->cameraRect->w >= this->levelWidth){
		this->cameraRect->x = this->levelWidth - this->windowWidth;
	}
	if (this->cameraRect->y + this->cameraRect->h >= this->levelHeight)
		this->cameraRect->y = this->levelHeight - this->windowHeight;
}

SDL_Rect* Camera::getCamera(){
	return this->cameraRect;
}
