#pragma once
#include "Box2D/Box2D.h"
#include <SDL.h>
#include "DrawContainer.h"
#include "UpdateContainer.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "ContactHandler.h"
#include "MapDrawer.h"
#include "TDCar.h"
#include "Camera.h"
#include <Windows.h>
#include "Tree.h"
#include "Sprite.h"
#include "Projectile.h"
#include "Collectible.h"
#include "Sound.h"
#include "FPS.h"
#include "Hud.h"

/************************************************************************/
/* The World class contains everything a the game needs to render except
for the window. Its purpose is to render the world, run the physics
update the objects, etc. Not all in this class of course.			*/
/************************************************************************/

enum GameState { GameState_Running, GameState_Paused, GameState_In_MainMenu, GameState_Closing };

class World
{
private:
	Hud *hud;
	TDCar* myCar;
	Tree* myTree;
	Sound* sound;
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
	PauseMenu* pauseMenu;

	int mouseX, mouseY;

	//physics
	const b2Vec2 *gravity;
	const int32 *velocityIterations;
	const int32 *positionIterations;
	b2World *physics;
	std::vector<b2Body*> *bodyRemoveStack;
	std::vector<Projectile*> *projectileRemoveStack;
	std::vector<Projectile*> *activeProjectiles;
	std::vector<Collectible*> *collectibleRemoveStack;
	std::vector<Collectible*> *activeCollectibles;
	//Containers
	DrawContainer *drawContainer;
	UpdateContainer *updateContainer;
	ContactHandler *contactHandler;

	//other
	int prevTime;
	int currentTime;
	float deltaTime;
	GameState currentGameState;

	MapDrawer *mapDrawer;
		
	void tick();

	float calcDeltaTime();
	SDL_Texture *loadTexture(std::string filePath, SDL_Renderer *renderTarget);
	void createCamera(SDL_Window *window, int levelWidth, int levelHeight);
	void handleBodyRemoveStack();
	void handleProjectileRemoveStack();
	void handleCollectibleRemoveStack();

	SDL_Point * center;
	//CAR

	SDL_Texture *textureCar;
	SDL_Surface *surfaceCar;

	FPS *fpsCounter;

public:
	World(SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font);
	~World();
	void run();
	void setGameState( GameState gameState );

	//Box2d wrapper function
	b2Body* createBody(b2BodyDef *bodyDef);
	void destroyBody(b2Body *body);
	int transfrom(float);
	void drawObject(float nwidth, float nheight, float nx, float ny, float nangle);
	Uint32 getFPS();
	void addProjectile( Projectile* projectile );
	void destroyProjectile( Projectile* projectile );

	void addCollectible(int w, int h, int x, int y);
	void destroyCollectible(Collectible *collectible);
};


