#ifndef CAMERA_H
#define CAMERA_H
#include "SDL.h"
#include "Random.h"

class Camera
{
private:
	SDL_Rect* cameraRect;
	int width;
	int height;
	float cameraShakeTime;
	int shakeMagnitude;

public:
	int levelWidth, levelHeight, windowWidth, windowHeight;
	Camera::Camera(int levelWidth, int levelHeight, int windowWidth, int windowHeight);
	Camera::~Camera(void);

	void update(int originX, int originY, float deltaTime);
	SDL_Rect* getCamera();
	void cameraShake( float time, int magnitude = 3 );
};

#endif

