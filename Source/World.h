#pragma once
#include "Box2D/Box2D.h"
#include <SDL.h>
#include "DrawContainer.h"
#include "UpdateContainer.h"
#include "MainMenu.h"
#include "Player.h"
#include "MapDrawer.h"
#include "TDCar.h"
#include "Camera.h"
#include <Windows.h>
#include "Tree.h"
/************************************************************************/
/* The World class contains everything a the game needs to render except
for the window. Its purpose is to render the world, run the physics
update the objects, etc. Not all in this class of course.			*/
/************************************************************************/
const int scale = 10;
class World
{
private:

	TDCar* myCar;
	Tree* myTree;
	Tree* myTree2;
	//SDL
	SDL_Renderer *renderTarget;
	SDL_Texture *carTexture;
	SDL_Texture *mainMenuBackground;
	Camera* camera;
	SDL_Event ev;
	void updateSDL();
	const Uint8 *keyState;
	int m_controlState;
	//Menus
	MainMenu* menu;


	//physics
	const b2Vec2 *gravity;
	const int32 *velocityIterations;
	const int32 *positionIterations;
	b2World *physics;
	std::vector<b2Body*> *bodyRemoveStack;
	//Containers
	DrawContainer *drawContainer;
	UpdateContainer *updateContainer;

	//other
	int prevTime;
	int currentTime;
	float deltaTime;
	bool isRunning;

	MapDrawer *mapDrawer;
		
	void tick();

	float calcDeltaTime();
	SDL_Texture *loadTexture(std::string filePath, SDL_Renderer *renderTarget);
	void createCamera(SDL_Window *window, int levelWidth, int levelHeight);
	void handleBodyRemoveStack();

	SDL_Point * center;
	//CAR

	SDL_Texture *textureCar;
	SDL_Surface *surfaceCar;
public:
	Player *player1;
	World(SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font);
	~World();
	void run();
	void drawCar();
	
	//Box2d wrapper function
	b2Body* createBody(b2BodyDef *bodyDef);
	void destroyBody(b2Body *body);
	int transfrom(float);
	void drawObject(float nwidth, float nheight, float nx, float ny, float nangle);
	
};


