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
	bodyRemoveStack = new std::vector<B2Content*>();
	projectileRemoveStack = new std::vector<Projectile*>();
	explosionRemoveStack = new std::vector<Explosion*>();
	activeProjectiles = new std::vector<Projectile*>();
	explosions = new std::vector<Explosion*>();
	objects = new std::vector<B2Content*>();

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
	mainMenuBackground = Assets::getInstance()->getAsset(Asset_MainMenu_Background);
	menu = new MainMenu( renderTarget, window, mainMenuBackground, camera, font );

	//Paused screen
	pauseMenu = new PauseMenu(this, renderTarget, camera);

	//Creation of sprites should be placed elsewhere as well, I'm just running out of time
	mapDrawer = new MapDrawer(renderTarget, camera->getCamera(), this);
	drawContainer->add( mapDrawer );
	updateContainer->add( mapDrawer );

	myCar = new TDCar( this, physics, renderTarget, 3, 6 );
	drawContainer->add(myCar);
	updateContainer->add(myCar);

	addObject( new Tree( this, physics, renderTarget, 10, 10, 20, -15 ));
	addObject( new Tree( this, physics, renderTarget, 10, 10, 40, -30 ));
	myTurret = new Turret(physics, renderTarget, 50, -40, myCar, this);
	drawContainer->add(myTurret);
	updateContainer->add(myTurret);
	std::vector<TDTire*> tires = myCar->getTires();
	for (size_t i = 0; i < tires.size(); i++)
		drawContainer->add(tires[i]);
	drawContainer->add( myCar );

	contactHandler = new ContactHandler(this);
	physics->SetContactListener( contactHandler );
}


World::~World()
{
	for( size_t i = 0; i < activeProjectiles->size(); i++ )
	{
		delete activeProjectiles->at( i );
	}
	delete activeProjectiles;						activeProjectiles = nullptr;
	for( size_t c = 0; c < objects->size(); c++ )
	{
		delete objects->at( c );					objects->at( c ) = nullptr;
	}
	delete objects;									objects = nullptr;
	for( size_t x = 0; x < explosions->size(); x++ )
	{
		delete explosions->at( x );					explosions->at( x ) = nullptr;
	}
	delete explosions;								explosions = nullptr;
	delete myCar;									myCar = nullptr;
	delete myTurret;								myTurret = nullptr;
	delete mapDrawer;								mapDrawer = nullptr;
	handleBodyRemoveStack();
	handleProjectileRemoveStack();
	handleExplosionRemoveStack();
	delete bodyRemoveStack;							bodyRemoveStack = nullptr;
	delete projectileRemoveStack;					projectileRemoveStack = nullptr;
	delete explosionRemoveStack;					explosionRemoveStack = nullptr;
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
		handleExplosionRemoveStack();
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

void World::handleBodyRemoveStack(){
	for (size_t i = 0; i < bodyRemoveStack->size(); i++){
		updateContainer->remove( bodyRemoveStack->at( i ) );
		drawContainer->remove( bodyRemoveStack->at( i ) );
		delete bodyRemoveStack->at( i );
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

void World::handleExplosionRemoveStack()
{
	for( size_t i = 0; i < explosionRemoveStack->size(); i++ )
	{
		drawContainer->remove( explosionRemoveStack->at( i ) );
		updateContainer->remove( explosionRemoveStack->at( i ) );
		delete explosionRemoveStack->at( i );
		explosionRemoveStack->at( i ) = nullptr;
	}
	explosionRemoveStack->clear();
}

void World::destroyProjectile( Projectile *projectile )
{
	activeProjectiles->erase( std::remove( activeProjectiles->begin(), activeProjectiles->end(), projectile ), activeProjectiles->end() );
	projectileRemoveStack->push_back( projectile );
}

void World::createExplosion(SDL_Rect positionRect)
{
	Explosion* newExplosion = new Explosion(renderTarget, this, positionRect);
	explosions->push_back( newExplosion );
	updateContainer->add( newExplosion );
	drawContainer->add( newExplosion );
}

void World::removeExplosion( Explosion* explosion )
{
	explosions->erase( std::remove( explosions->begin(), explosions->end(), explosion ), explosions->end() );
	explosionRemoveStack->push_back( explosion );
}

void World::destroyObject(B2Content *object){
	objects->erase( std::remove( objects->begin(), objects->end(), object ), objects->end() );
	bodyRemoveStack->push_back(object);
}

void World::addProjectile( Projectile *projectile )
{	
	updateContainer->add( projectile );
	drawContainer->add( projectile );
	activeProjectiles->push_back( projectile );
}

void World::addObject( B2Content* object )
{
	objects->push_back( object );
	updateContainer->add( object );
	drawContainer->add( object );
}