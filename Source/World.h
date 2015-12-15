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
#include "Turret.h"
#include "Explosion.h"

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
	Sound* sound;
	Turret* myTurret;
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
	std::vector<B2Content*> *bodyRemoveStack;
	std::vector<Projectile*> *projectileRemoveStack;
	std::vector<Explosion*> *explosionRemoveStack;
	std::vector<Projectile*> *activeProjectiles;
	std::vector<Collectible*> *collectibleRemoveStack;
	std::vector<Collectible*> *activeCollectibles;
	std::vector<Explosion*> *explosions;
	std::vector<B2Content*> *objects;

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
	void createCamera(SDL_Window *window, int levelWidth, int levelHeight);
	void handleBodyRemoveStack();
	void handleProjectileRemoveStack();
	void handleCollectibleRemoveStack();

	SDL_Point * center;
	//CAR

	SDL_Texture *textureCar;
	SDL_Surface *surfaceCar;

	FPS *fpsCounter;
	void handleExplosionRemoveStack();

public:
	World(SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font);
	~World();
	void run();
	void setGameState( GameState gameState );

	//Box2d wrapper function
	void destroyObject( B2Content* body );
	void addObject( B2Content* object );
	int transfrom(float);
	void drawObject(float nwidth, float nheight, float nx, float ny, float nangle);
	Uint32 getFPS();
	void addProjectile( Projectile* projectile );
	void destroyProjectile( Projectile* projectile );

	void addCollectible(int w, int h, int x, int y, Collectible::Collectibletypes);
	void destroyCollectible(Collectible *collectible);
	void createExplosion( SDL_Rect positionRect );
	void removeExplosion( Explosion* explosion );

	TDCar* getCar();
};


