#include "World.h"

World::World(SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font)
{
	//Should these be pointers? No
	this->prevTime = 0;
	this->currentTime = 0;
	this->deltaTime = 0.0f;

	this->velocityIterations = new int32(8);
	this->positionIterations = new int32(3);

	//create physics world (box2d)
	this->gravity = new b2Vec2(0.0f, 0.0f);
	this->physics = new b2World(*gravity);

	//create graphics world (SDL)
	this->renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//TODO: Level in separate class, camera too maybe?
	this->createCamera(window, levelWidth, levelHeight);

	//Create containers
	this->drawContainer = new DrawContainer(renderTarget, cameraRect);
	this->updateContainer = new UpdateContainer();

	//TODO: main menu in separate class, drawable maybe?
	this->mainMenuBackground = LoadTexture("Images/Mainmenu/background.png", renderTarget);
	MainMenu menu(renderTarget, mainMenuBackground, this->camera->getCamera(), font);
	menu.showMenu(renderTarget);

	//Creation of sprites should be placed elsewhere as well, I'm just running out of time
	player1 = new Player(renderTarget, 0, 0, 300.0f, drawContainer);
}


World::~World()
{
	delete physics;
	delete gravity;
	delete velocityIterations;
	delete positionIterations;
	delete mainMenuBackground;
}

//Update the world
void World::tick()
{
	calcDeltaTime();

	//update physics
	physics->Step(deltaTime, *velocityIterations, *positionIterations);

	//update camera
	//TODO: make camera IUpdateable.
	camera->Update(player1->getPositionX(), player1->getPositionY());

	updateContainer->Update(deltaTime);

	//update SDL
	updateSDL();
}

void World::Run(){
	bool isRunning = true;

	while (isRunning){
		tick();
	}

	SDL_DestroyRenderer(renderTarget);
	renderTarget = nullptr;
}

void World::updateSDL(){

	SDL_RenderClear(renderTarget);
	drawContainer->Draw();
	SDL_RenderPresent(renderTarget);
}

float World::calcDeltaTime(){
	prevTime = currentTime;
	currentTime = SDL_GetTicks();
	deltaTime = (currentTime - prevTime) / 1000.0f;
	return deltaTime;
}

void World::createCamera(SDL_Window *window, int levelWidth, int levelHeight)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(window, &width, &height);
	camera = new Camera(levelWidth, levelHeight, width, height);
}

SDL_Texture* World::LoadTexture(std::string filePath, SDL_Renderer *renderTarget){
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);
	return texture;
}