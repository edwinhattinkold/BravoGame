#ifndef CAMERA_H
#define CAMERA_H
#include "SDL.h"

class Camera
{
private:
	SDL_Rect cameraRect;

public:
	int levelWidth, levelHeight, windowWidth, windowHeight;
	Camera::Camera(int levelWidth, int levelHeight, int windowWidth, int windowHeight);
	Camera::~Camera(void);

	void Camera::Update(int originX, int originY);
	SDL_Rect Camera::getCamera();
};

#endif

