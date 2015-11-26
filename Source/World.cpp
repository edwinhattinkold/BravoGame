#include "World.h"
#include "CustomCursor.h"
#include "Assets.h"

World::World( SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font )
{
	prevTime = 0;
	currentTime = 0;
	deltaTime = 0.0f;
	m_controlState = 0;

	velocityIterations = new int32( 8 );
	positionIterations = new int32( 3 );

	//create add and remove stacks
	bodyRemoveStack = new std::vector<b2Body*>();
	projectileRemoveStack = new std::vector<Projectile*>();
	activeProjectiles = new std::vector<Projectile*>();

	//create physics world (box2d)
	gravity = new b2Vec2( 0.0f, 0.0f );
	physics = new b2World( *gravity );

	//create graphics world (SDL)
	renderTarget = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	CustomCursor::getInstance()->setRenderTarget( renderTarget );
	Assets::getInstance()->setRenderTarget( renderTarget );
	sound = Sound::getInstance();

	//TODO: Level in separate class, camera too maybe?
	createCamera( window, levelWidth, levelHeight );

	//Create containers
	drawContainer = new DrawContainer( renderTarget, camera->getCamera() );
	updateContainer = new UpdateContainer();

	//TODO: main menu in separate class, drawable maybe?
	mainMenuBackground = loadTexture( "Images/Mainmenu/background.png", renderTarget );
	menu = new MainMenu( renderTarget, window, mainMenuBackground, camera, font );

	//Paused screen
	pauseMenu = new PauseMenu(this, renderTarget, camera);

	//Creation of sprites should be placed elsewhere as well, I'm just running out of time
	mapDrawer = new MapDrawer( renderTarget, camera->getCamera(),this );
	
	myCar = new TDCar(this, physics, renderTarget, 3, 6);

	myTree = new Tree(physics, renderTarget, 6, 10, 20, -15);
	myTree2 = new Tree( physics, renderTarget, 6, 10, 40, -30 );

	//myTree2 = new Tree(physics, renderTarget, 4, 4, 30, -15);


	drawContainer->add(mapDrawer);

	drawContainer->add(myTree);
	drawContainer->add(myTree2);
	updateContainer->add( mapDrawer );
	updateContainer->add( myCar );
		
	std::vector<TDTire*> tires = myCar->getTires();
	for (int i = 0; i < tires.size(); i++)
		drawContainer->add(tires[i]);
	drawContainer->add( myCar );

	contactHandler = new ContactHandler(this);
	physics->SetContactListener( contactHandler );
}


World::~World()
{
	for( size_t c = 0; c < activeProjectiles->size(); c++ )
	{
		delete activeProjectiles->at( c );
	}
	delete activeProjectiles;						activeProjectiles = nullptr;
	delete myCar;									myCar = nullptr;
	delete myTree;									myTree = nullptr;
	delete myTree2;									myTree2 = nullptr;
	delete mapDrawer;								mapDrawer = nullptr;
	handleBodyRemoveStack();
	handleProjectileRemoveStack();
	delete bodyRemoveStack;							bodyRemoveStack = nullptr;
	delete projectileRemoveStack;					projectileRemoveStack = nullptr;
	delete physics;									physics = nullptr;
	delete gravity;									gravity = nullptr;
	delete velocityIterations;						velocityIterations = nullptr;
	delete positionIterations;						positionIterations = nullptr;
	delete camera;									camera = nullptr;
	delete menu;									menu = nullptr;
	delete pauseMenu;								pauseMenu = nullptr;
	delete drawContainer;							drawContainer = nullptr;
	delete updateContainer;							updateContainer = nullptr;
	delete contactHandler;							contactHandler = nullptr;

	SDL_DestroyTexture(mainMenuBackground);			mainMenuBackground = nullptr;
	SDL_DestroyRenderer(renderTarget);				renderTarget = nullptr;
}

//Update the world
void World::tick()
{
	//DeltaTime
	calcDeltaTime();

	//Input handling
	while( SDL_PollEvent( &ev ) != 0 )
	{
		switch( ev.type )
		{
			case(SDL_QUIT):
				currentGameState = GameState_Closing;
				break;
			case(SDL_MOUSEMOTION) :
				mouseX = ev.motion.x;
				mouseY = ev.motion.y;
				break;
			case(SDL_KEYDOWN) :
				if( ev.key.keysym.sym == SDLK_ESCAPE )
				{
					currentGameState == GameState_Running ? currentGameState = GameState_Paused : currentGameState = GameState_Running;
					pauseMenu->center();
					if( currentGameState == GameState_Paused )
						sound->pauseAllSounds();
				}
				else if( currentGameState == GameState_Paused )
					pauseMenu->handleKeyboardInput( ev.key.keysym.sym );
				break;
			case(SDL_MOUSEBUTTONDOWN) :
				if( currentGameState == GameState_Paused )
					pauseMenu->mouseButtonClicked(mouseX, mouseY);
				break;
		}
	}
	keyState = SDL_GetKeyboardState( NULL );

	//SVEN
	
	if( currentGameState != GameState_Paused )
	{
		updateContainer->update( deltaTime, keyState );
		physics->Step( deltaTime, *velocityIterations, *positionIterations );//update physics
		camera->update( myCar->getOriginX(), myCar->getOriginY() );
	}

	//update SDL
	updateSDL();

	if( currentGameState != GameState_Paused )
	{
		handleProjectileRemoveStack();
		handleBodyRemoveStack();
	}
}


void World::run()
{
	setGameState( GameState_In_MainMenu );
	

	while( currentGameState != GameState_Closing)
		tick();

	SDL_DestroyRenderer( renderTarget );
	renderTarget = nullptr;
}

void World::setGameState( GameState gameState )
{
	currentGameState = gameState;

	if( currentGameState == GameState_In_MainMenu ) 
	{ 
		int i = menu->showMenu( renderTarget );
		if( i == menu->getExitCode() )
			currentGameState = GameState_Closing;
		else
			currentGameState = GameState_Running;
	}
}

void World::updateSDL()
{
	SDL_RenderClear( renderTarget );
	drawContainer->draw();
	if( currentGameState == GameState_Paused )
		pauseMenu->tick( mouseX, mouseY );
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

void World::handleProjectileRemoveStack()
{
	for( size_t i = 0; i < projectileRemoveStack->size(); i++ )
	{
		updateContainer->remove( projectileRemoveStack->at( i ) );
		drawContainer->remove( projectileRemoveStack->at( i ) );
		delete projectileRemoveStack->at( i );
		projectileRemoveStack->at( i ) = nullptr;
	}
	projectileRemoveStack->clear();
}

void World::destroyProjectile( Projectile *projectile )
{
	activeProjectiles->erase( std::remove( activeProjectiles->begin(), activeProjectiles->end(), projectile ), activeProjectiles->end() );
	projectileRemoveStack->push_back( projectile );
}

//Box2D function wrappers;
b2Body* World::createBody(b2BodyDef *def){
	return physics->CreateBody(def);
}

void World::destroyBody(b2Body *body){
	bodyRemoveStack->push_back(body);
}

void World::addProjectile( Projectile *projectile )
{	
	updateContainer->add( projectile );
	drawContainer->add( projectile );
	activeProjectiles->push_back( projectile );
}