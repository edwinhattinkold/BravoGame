#pragma once
#include "Box2D/Box2D.h"
#include <SDL.h>
#include "DrawContainer.h"
#include "UpdateContainer.h"
#include "MainMenu.h"
#include "Player.h"
#include "MapDrawer.h"
#include "Camera.h"
/************************************************************************/
/* The World class contains everything a the game needs to render except
for the window. Its purpose is to render the world, run the physics
update the objects, etc. Not all in this class of course.			*/
/************************************************************************/
class World
{
private:
	//SDL
	SDL_Renderer *renderTarget;
	SDL_Rect *cameraRect;
	SDL_Texture *mainMenuBackground;
	Camera* camera;
	SDL_Event ev;
	void updateSDL();

	//Menus
	MainMenu* menu;

	//physics
	const b2Vec2 *gravity;
	const int32 *velocityIterations;
	const int32 *positionIterations;
	b2World *physics;

	//Containers
	DrawContainer *drawContainer;
	UpdateContainer *updateContainer;

	//other
	int prevTime;
	int currentTime;
	float deltaTime;
	bool isRunning;

	Player *player1;
	MapDrawer *mapDrawer;

	void tick();

	float calcDeltaTime();
	SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget);
	void createCamera(SDL_Window *window, int levelWidth, int levelHeight);
public:
	World(SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font);
	~World();
	void Run();
};


