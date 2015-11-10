#include "World.h"
#include "CustomCursor.h"


World::World( SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font )
{
	prevTime = 0;
	currentTime = 0;
	deltaTime = 0.0f;
	isRunning = true;
	m_controlState = 0;


	velocityIterations = new int32( 8 );
	positionIterations = new int32( 3 );

	//create add and remove stacks
	bodyRemoveStack = new std::vector<b2Body*>();

	//create physics world (box2d)
	gravity = new b2Vec2( 0.0f, 0.0f );
	physics = new b2World( *gravity );

	//create graphics world (SDL)
	renderTarget = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	CustomCursor::getInstance()->setRenderTarget( renderTarget );

	//TODO: Level in separate class, camera too maybe?
	createCamera( window, levelWidth, levelHeight );

	//Create containers
	drawContainer = new DrawContainer( renderTarget, camera->getCamera() );
	updateContainer = new UpdateContainer();

	//TODO: main menu in separate class, drawable maybe?
	mainMenuBackground = loadTexture( "Images/Mainmenu/background.png", renderTarget );
	arrow = loadTexture( "Images/Car/arrow.png", renderTarget );
	menu = new MainMenu( renderTarget, window, mainMenuBackground, camera, font );

	//Creation of sprites should be placed elsewhere as well, I'm just running out of time
	mapDrawer = new MapDrawer( renderTarget, camera->getCamera(),this );
	
	myCar = new TDCar(physics, renderTarget, 6, 10);

	myTree = new Tree(physics, renderTarget, 3, 6, 0, 0);


	drawContainer->add(mapDrawer);
	drawContainer->add( myCar );
	drawContainer->add(myTree);
	updateContainer->add( mapDrawer );
}


World::~World()
{
	delete this->myCar;								this->myCar = nullptr;;
	delete this->mapDrawer;							this->mapDrawer = nullptr;
	handleBodyRemoveStack();
	delete bodyRemoveStack;							bodyRemoveStack = nullptr;
	delete this->physics;							this->physics = nullptr;
	delete this->gravity;							this->gravity = nullptr;
	delete this->velocityIterations;				this->velocityIterations = nullptr;
	delete this->positionIterations;				this->positionIterations = nullptr;
	delete this->camera;							this->camera = nullptr;
	delete this->menu;								this->menu = nullptr;
	delete drawContainer;						this->drawContainer = nullptr;
	delete updateContainer;					this->updateContainer = nullptr;

	SDL_DestroyTexture(this->mainMenuBackground);	this->mainMenuBackground = nullptr;
	SDL_DestroyRenderer(this->renderTarget);		this->renderTarget = nullptr;
}

//Update the world
void World::tick()
{
	//DeltaTime
	calcDeltaTime();

	//Input handling
	while (SDL_PollEvent(&ev) != 0)
	{
		if (ev.type == SDL_QUIT)
			isRunning = false;
		if (ev.key.keysym.sym == SDLK_ESCAPE)
		{
			Sound::getInstance()->playSoundLooping(Sound_MainMenu_Theme);
			int i = menu->showMenu(renderTarget);
			if (i == menu->getExitCode())
				isRunning = false;
		}
	}
	keyState = SDL_GetKeyboardState(NULL);

	//SVEN
	
	myCar->update(keyState);

	///SVEN
	handleBodyRemoveStack();
	//update physics
	physics->Step(deltaTime, *velocityIterations, *positionIterations);

	camera->update(myCar->getOriginX(), myCar->getOriginY());
	//camera->update(0,0);

	updateContainer->update(deltaTime, keyState);

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
	SDL_Rect srcrect;
	SDL_Rect dstrect;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 50;
	srcrect.h = 50;
	dstrect.x = 0 - camera->getCamera()->x;
	dstrect.y = 0 - camera->getCamera()->y;
	dstrect.w = 50;
	dstrect.h = 50;	
	
	drawContainer->draw();
	SDL_RenderCopy( renderTarget, arrow, &srcrect, &dstrect );
	int scale = 20;
	//std::cout << "x " << myCar->getPosition().x << "y " << myCar->getPosition().y * scale << "" << std::endl;
	
	
	
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