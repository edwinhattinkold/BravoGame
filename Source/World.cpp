#include "World.h"


World::World(SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font)
{
	this->prevTime = 0;
	this->currentTime = 0;
	this->deltaTime = 0.0f;
	this->isRunning = true;

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
	this->drawContainer = new DrawContainer(renderTarget, this->camera->getCamera());
	this->updateContainer = new UpdateContainer();

	//TODO: main menu in separate class, drawable maybe?
	this->mainMenuBackground = LoadTexture("Images/Mainmenu/background.png", renderTarget);
	this->menu = new MainMenu(renderTarget, mainMenuBackground, this->camera->getCamera(), font);

	//Creation of sprites should be placed elsewhere as well, I'm just running out of time
	this->player1 = new Player(renderTarget, 0, 0, 300.0f, drawContainer);
	this->mapDrawer = new MapDrawer(renderTarget);

	this->drawContainer->Add(this->mapDrawer);
	this->drawContainer->Add(this->player1);

	this->updateContainer->Add(this->player1);
}


World::~World()
{
	delete this->physics;							this->physics = nullptr;
	delete this->gravity;							this->gravity = nullptr;
	delete this->velocityIterations;				this->velocityIterations = nullptr;
	delete this->positionIterations;				this->positionIterations = nullptr;
	delete this->drawContainer;						this->drawContainer = nullptr;
	delete this->updateContainer;					this->updateContainer = nullptr;
	delete this->camera;							this->camera = nullptr;
	delete this->menu;								this->menu = nullptr;
	delete this->player1;							this->player1 = nullptr;
	delete this->mapDrawer;							this->mapDrawer = nullptr;
	SDL_DestroyTexture(this->mainMenuBackground);	this->mainMenuBackground = nullptr;
	SDL_DestroyRenderer(this->renderTarget);		this->renderTarget = nullptr;
}

//Update the world
void World::tick()
{
	//DeltaTime
	this->calcDeltaTime();

	//Input handling
	while (SDL_PollEvent(&ev) != 0){
		if (ev.type == SDL_QUIT)
			this->isRunning = false;
		if (ev.key.keysym.sym == SDLK_ESCAPE){
			Sound::getInstance()->playSoundLooping("rock_intro.mp3");
			int i = this->menu->showMenu(renderTarget);
			if (i == this->menu->getExitCode())
				this->isRunning = false;
		}
	}

	this->keyState = SDL_GetKeyboardState(NULL);

	//update physics
	this->physics->Step(deltaTime, *velocityIterations, *positionIterations);

	//update camera
	//TODO: make camera IUpdateable.  <-- klinkt netjes, maar is niet slim, aangezien de camera altijd als eerst geupdate MOET worden
	//zodat alle ander updates gegevens uit de geupdate camera kunnen halen, als je het in een vector op positie 0 zet dan kan een ander stuk code
	//een element op de 0ste plek zetten, waardoor alles omvalt.
	this->camera->Update(player1->getPositionX(), player1->getPositionY());

	this->updateContainer->Update(deltaTime, keyState);

	//update SDL
	this->updateSDL();
}

void World::Run(){
	this->isRunning = true;

	//Show the menu
	int i = this->menu->showMenu(renderTarget);
	if (i == this->menu->getExitCode())
		this->isRunning = false;

	while (isRunning)
		this->tick();

	SDL_DestroyRenderer(renderTarget);
	this->renderTarget = nullptr;
}

void World::updateSDL(){
	SDL_RenderClear(renderTarget);
	this->drawContainer->Draw();
	SDL_RenderPresent(renderTarget);
}

float World::calcDeltaTime(){
	this->prevTime = this->currentTime;
	this->currentTime = SDL_GetTicks();
	this->deltaTime = (this->currentTime - this->prevTime) / 1000.0f;
	return this->deltaTime;
}

void World::createCamera(SDL_Window *window, int levelWidth, int levelHeight)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(window, &width, &height);
	this->camera = new Camera(levelWidth, levelHeight, width, height);
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