#ifndef CAMERA_H
#define CAMERA_H
#include "SDL.h"

class Camera
{
private:
	SDL_Rect* cameraRect;
	int width;
	int height;

public:
	int levelWidth, levelHeight, windowWidth, windowHeight;
	Camera::Camera(int levelWidth, int levelHeight, int windowWidth, int windowHeight);
	Camera::~Camera(void);

	void update(int originX, int originY);
	SDL_Rect* getCamera();
};

#endif

