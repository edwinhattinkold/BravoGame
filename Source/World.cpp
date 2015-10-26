#include "World.h"


World::World( SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font )
{
	prevTime = 0;
	currentTime = 0;
	deltaTime = 0.0f;
	isRunning = true;

	velocityIterations = new int32( 8 );
	positionIterations = new int32( 3 );

	//create add and remove stacks
	bodyRemoveStack = new std::vector<b2Body*>();

	//create physics world (box2d)
	gravity = new b2Vec2( 0.0f, 0.0f );
	physics = new b2World( *gravity );

	//create graphics world (SDL)
	renderTarget = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	//TODO: Level in separate class, camera too maybe?
	createCamera( window, levelWidth, levelHeight );

	//Create containers
	drawContainer = new DrawContainer( renderTarget, camera->getCamera() );
	updateContainer = new UpdateContainer();

	//TODO: main menu in separate class, drawable maybe?
	mainMenuBackground = loadTexture( "Images/Mainmenu/background.png", renderTarget );
	menu = new MainMenu( renderTarget, mainMenuBackground, camera->getCamera(), font );

	//Creation of sprites should be placed elsewhere as well, I'm just running out of time
	player1 = new Player( renderTarget, 1024, 1024, 300.0f, drawContainer );
	mapDrawer = new MapDrawer( renderTarget, camera->getCamera(),this );
	drawContainer->add( mapDrawer );
	drawContainer->add( player1 );
	updateContainer->add( mapDrawer );
	updateContainer->add( player1 );
}


World::~World()
{
	delete this->drawContainer;						this->drawContainer = nullptr;
	delete this->updateContainer;					this->updateContainer = nullptr;
	delete this->mapDrawer;							this->mapDrawer = nullptr;
	handleBodyRemoveStack();
	delete bodyRemoveStack;							bodyRemoveStack = nullptr;
	delete this->physics;							this->physics = nullptr;
	delete this->gravity;							this->gravity = nullptr;
	delete this->velocityIterations;				this->velocityIterations = nullptr;
	delete this->positionIterations;				this->positionIterations = nullptr;
	delete this->camera;							this->camera = nullptr;
	delete this->menu;								this->menu = nullptr;
	delete this->player1;							this->player1 = nullptr;
	
	SDL_DestroyTexture(this->mainMenuBackground);	this->mainMenuBackground = nullptr;
	SDL_DestroyRenderer(this->renderTarget);		this->renderTarget = nullptr;
}

//Update the world
void World::tick()
{
	//DeltaTime
	calcDeltaTime();

	//Input handling
	while( SDL_PollEvent( &ev ) != 0 )
	{
		if( ev.type == SDL_QUIT )
			isRunning = false;
		if( ev.key.keysym.sym == SDLK_ESCAPE )
		{
			Sound::getInstance()->playSoundLooping( Sound_MainMenu_Theme );
			int i = menu->showMenu( renderTarget );
			if( i == menu->getExitCode() )
				isRunning = false;
		}
	}
	keyState = SDL_GetKeyboardState( NULL );
	handleBodyRemoveStack();
	//update physics
	physics->Step( deltaTime, *velocityIterations, *positionIterations );

	//update camera
	//TODO: make camera IUpdateable.  <-- klinkt netjes, maar is niet slim, aangezien de camera altijd als eerst geupdate MOET worden
	//zodat alle ander updates gegevens uit de geupdate camera kunnen halen, als je het in een vector op positie 0 zet dan kan een ander stuk code
	//een element op de 0ste plek zetten, waardoor alles omvalt.
	camera->update( player1->getPositionX(), player1->getPositionY() );

	updateContainer->update( deltaTime, keyState );

	//update SDL
	updateSDL();
}

void World::run()
{
	isRunning = true;

	//Show the menu
	int i = menu->showMenu( renderTarget );
	if( i == menu->getExitCode() )
		isRunning = false;

	while( isRunning )
		tick();

	SDL_DestroyRenderer( renderTarget );
	renderTarget = nullptr;
}

void World::updateSDL()
{
	SDL_RenderClear( renderTarget );
	drawContainer->draw();
	SDL_RenderPresent( renderTarget );
}

float World::calcDeltaTime()
{
	prevTime = currentTime;
	currentTime = SDL_GetTicks();
	deltaTime = ( currentTime - prevTime ) / 1000.0f;
	return deltaTime;
}

void World::createCamera( SDL_Window *window, int levelWidth, int levelHeight )
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize( window, &width, &height );
	camera = new Camera( levelWidth, levelHeight, width, height );
}

SDL_Texture* World::loadTexture( std::string filePath, SDL_Renderer *renderTarget )
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load( filePath.c_str() );
	if( surface == NULL )
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface( renderTarget, surface );
		if( texture == NULL )
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface( surface );
	return texture;
}

void World::handleBodyRemoveStack(){
	for (size_t i = 0; i < bodyRemoveStack->size(); i++){
		physics->DestroyBody(bodyRemoveStack->at(i));
		bodyRemoveStack->at(i) = nullptr;
	}
	bodyRemoveStack->clear();
}

//Box2D function wrappers;
b2Body* World::createBody(b2BodyDef *def){
	return physics->CreateBody(def);
}

void World::destroyBody(b2Body *body){
	bodyRemoveStack->push_back(body);
}