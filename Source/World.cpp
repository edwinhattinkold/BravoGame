#include "World.h"
#include "CustomCursor.h"
#include "Assets.h"
#include "HighscoreMenu.h"
#include "MovingTurret.h"

World::World( SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font )
{
	fastForward = false;
	fpsCounter = new FPS();

	//create graphics world (SDL)
	renderTarget = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	CustomCursor::getInstance()->setRenderTarget( renderTarget );
	Assets::getInstance()->setRenderTarget( renderTarget );
	sound = Sound::getInstance();

	createCamera( window, levelWidth, levelHeight );

	//TODO: main menu in separate class, drawable maybe?
	mainMenuBackground = Assets::getInstance()->getAsset(Asset_MainMenu_Background);
	menu = new MainMenu( renderTarget, window, mainMenuBackground, camera, font, this );

	//Paused screen
	pauseMenu = new PauseMenu(this, renderTarget, camera);

	//GameOver screen
	gameOverMenu = new GameOverMenu( this, renderTarget, camera );
	winScreen = new WinScreen( this, renderTarget, camera );

	//HighScore screen
	highscoreMenu = new HighscoreMenu(this, renderTarget, camera);

	createPlayableContent();
}

void World::createPlayableContent()
{
	prevTime = 0;
	currentTime = 0;
	deltaTime = 0.0f;
	m_controlState = 0;

	velocityIterations = new int32( 8 );
	positionIterations = new int32( 3 );


	keys = new std::vector<Uint8 * >();
	

	//create add and remove stacks
	bodyRemoveStack = new std::vector<B2Content*>();
	projectileRemoveStack = new std::vector<Projectile*>();
	explosionRemoveStack = new std::vector<Explosion*>();
	activeProjectiles = new std::vector<Projectile*>();
	explosions = new std::vector<Explosion*>();
	objects = new std::vector<B2Content*>();

	collectibleRemoveStack = new std::vector<Collectible*>();
	activeCollectibles = new std::vector<Collectible*>();
	activeCollideObjects = new std::vector<CollideObject*>();

	//create physics world (box2d)
	gravity = new b2Vec2( 0.0f, 0.0f );
	physics = new b2World( *gravity );

	//Create containers
	drawContainer = new DrawContainer( renderTarget, camera->getCamera() );
	updateContainer = new UpdateContainer();

	//CAR
	myCar = new TDCar( this, physics, renderTarget, camera, 3, 6 );
	updateContainer->add( myCar );

	//add map

	mapDrawer = new MapDrawer( renderTarget, camera->getCamera(), this );
	drawContainer->add( mapDrawer );
	updateContainer->add( mapDrawer );

	//add collectables
	this->addCollectible(15, 15, 10, -100, Collectible::Collectibletypes::Oil);
	this->addCollectible(15, 15, 60, -100, Collectible::Collectibletypes::Oil);

	this->addCollectible(5, 5, 35, -150, Collectible::Collectibletypes::Collect);
	this->addCollectible(5, 5, 20, -50, Collectible::Collectibletypes::Gasoline);
	this->addCollectible(5, 5, 20, -80, Collectible::Collectibletypes::Nitro);
	this->addCollectible(5, 5, 30, -120, Collectible::Collectibletypes::Gasoline);
	this->addCollectible(5, 5, 40, -140, Collectible::Collectibletypes::Gasoline);
	this->addCollectible(5, 5, 40, -170, Collectible::Collectibletypes::Gasoline);
	this->addCollectible(5, 5, 40, -190, Collectible::Collectibletypes::Gasoline);
	this->addCollectible(5, 5, 40, -210, Collectible::Collectibletypes::Nitro);


	this->addCollectible(5, 5, 20, -329, Collectible::Collectibletypes::Gasoline);
	this->addCollectible(5, 5, 20, -350, Collectible::Collectibletypes::Gasoline);
	this->addCollectible(5, 5, 20, -380, Collectible::Collectibletypes::Nitro);
	this->addCollectible(5, 5, 30, -420, Collectible::Collectibletypes::Collect);
	this->addCollectible(5, 5, 40, -440, Collectible::Collectibletypes::Gasoline);
	this->addCollectible(5, 5, 40, -470, Collectible::Collectibletypes::Gasoline);
	this->addCollectible(5, 5, 40, -490, Collectible::Collectibletypes::Gasoline);
	this->addCollectible(5, 5, 40, -510, Collectible::Collectibletypes::Nitro);

	//add objects ( own destructor )
	std::vector<TDTire*> tires = myCar->getTires();
	for( size_t i = 0; i < tires.size(); i++ )
		drawContainer->add( tires[i] );
	drawContainer->add( myCar );

	//CAR
	surfaceCar = IMG_Load( "Images/Car/debugbuggy.png" );
	if( surfaceCar == NULL )
		std::cout << "Error" << std::endl;
	else
	{
		textureCar = SDL_CreateTextureFromSurface( renderTarget, surfaceCar );
		if( textureCar == NULL )
			std::cout << "Error 123 4 " << std::endl;
	}
	center = new SDL_Point;

	hud = new Hud(this, renderTarget, drawContainer, fpsCounter, camera, myCar, 24, 24, 0.8f );
	//hud = new Hud( renderTarget, drawContainer, fpsCounter, camera, myCar, 24, 24, 0.8f );

	drawContainer->add( hud );
	contactHandler = new ContactHandler( this );
	physics->SetContactListener( contactHandler );

	addCollidable(5, 5, 5, 0, CollideObject::Desert_Tree);
	addCollidable(5, 5, 15, 0, CollideObject::Ice_Tent);
	addCollidable(5, 5, 25, 0, CollideObject::Ice_Tree);
	addCollidable(5, 5, 35, 0, CollideObject::Desert_Piramid);
	addCollidable(5, 5, 45, 0, CollideObject::Collide_Default);

	addCollidable(5, 5, 5, 30, CollideObject::Desert_Tree);
	addCollidable(5, 5, 15, 30, CollideObject::Ice_Tent);
	addCollidable(5, 5, 25, 30, CollideObject::Ice_Tree);
	addCollidable(5, 5, 35, 30, CollideObject::Desert_Piramid);
	addCollidable(5, 5, 45, 30, CollideObject::Collide_Default);


	drawContainer->add( myCar );
}

void World::addTree( int x, int y )
{
	addObject( new Tree( this, physics, renderTarget, 10, 10, x, y ) );
}

void World::addMovingTurret(int x, int y)
{
	Turret* myTurret = new MovingTurret( physics, renderTarget, x, y, myCar, this );
	//drawContainer->add( myTurret );
	//updateContainer->add( myTurret );
	readyTurrets.push_back( myTurret );
}

void World::addTurret( int x, int y )
{
	Turret* myTurret = new Turret( physics, renderTarget, x, y, myCar, this );
	//drawContainer->add( myTurret );
	//updateContainer->add( myTurret );
	readyTurrets.push_back( myTurret );
}

World::~World()
{	
	delete this->fpsCounter;						this->fpsCounter = nullptr;

	delete menu;									menu = nullptr;
	delete pauseMenu;								pauseMenu = nullptr;
	delete gameOverMenu;							gameOverMenu = nullptr;
	delete highscoreMenu;							highscoreMenu = nullptr;
	delete winScreen;								winScreen = nullptr;
	delete camera;									camera = nullptr;

	destroyPlayableContent();

	SDL_DestroyTexture(mainMenuBackground);			mainMenuBackground = nullptr;
	SDL_DestroyRenderer(renderTarget);				renderTarget = nullptr;
}

void World::destroyPlayableContent()
{

	for( size_t i = 0; i < activeProjectiles->size(); i++ )
	{
		delete activeProjectiles->at( i );
	}
	delete activeProjectiles;						activeProjectiles = nullptr;
	for (size_t i = 0; i < activeCollectibles->size(); i++)
	{
		delete activeCollectibles->at(i);
	}
	delete activeCollectibles;						activeCollectibles = nullptr;

	for (size_t i = 0; i < activeCollideObjects->size(); i++)
	{
		delete activeCollideObjects->at(i);
	}
	delete activeCollideObjects;						activeCollideObjects = nullptr;
	

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
	for (size_t x = 0; x < keys->size(); x++)
	{
		delete keys->at(x);							keys->at(x) = nullptr;
	}
	for( size_t x = 0; x < turrets.size(); x++ )
	{
		delete turrets.at( x );							turrets.at( x ) = nullptr;
	}
	delete keys;									keys = nullptr;
	delete myCar;									myCar = nullptr;
	delete mapDrawer;								mapDrawer = nullptr;
	delete this->hud;								this->hud = nullptr;

	handleBodyRemoveStack();
	handleCollectibleRemoveStack();
	handleProjectileRemoveStack();
	handleExplosionRemoveStack();
	delete collectibleRemoveStack;					collectibleRemoveStack = nullptr;
	delete bodyRemoveStack;							bodyRemoveStack = nullptr;
	delete projectileRemoveStack;					projectileRemoveStack = nullptr;
	delete explosionRemoveStack;					explosionRemoveStack = nullptr;
	delete physics;									physics = nullptr;
	delete gravity;									gravity = nullptr;
	delete velocityIterations;						velocityIterations = nullptr;
	delete positionIterations;						positionIterations = nullptr;
	delete drawContainer;							drawContainer = nullptr;
	delete updateContainer;							updateContainer = nullptr;
	delete contactHandler;							contactHandler = nullptr;
	delete center;									center = nullptr;

}

void World::reset()
{
	MissionControl::getInstance().reset();
	destroyPlayableContent();
	createPlayableContent();
	myCar->health = myCar->maxHealth;
	myCar->takenDamage = 0;
}

TDCar* World::getCar()
{
	return myCar;
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
			case( SDL_KEYDOWN ) :
				if( ev.key.keysym.sym == SDLK_ESCAPE )
				{
					if (currentGameState == GameState_Running || currentGameState == GameState_Paused){
						currentGameState == GameState_Running ? currentGameState = GameState_Paused : currentGameState = GameState_Running;
						pauseMenu->center();
						if (currentGameState == GameState_Paused)
							sound->pauseAllSounds();
					}
				}
				else if( ev.key.keysym.sym == SDLK_LCTRL || ev.key.keysym.sym == SDLK_RCTRL )
					fastForward = !fastForward;
				else if( currentGameState == GameState_Paused )
					pauseMenu->handleKeyboardInput( ev.key.keysym.sym );
				else if( currentGameState == GameState_Game_Over )
					gameOverMenu->handleKeyboardInput( ev.key.keysym.sym );
				else if( currentGameState == GameState_In_Highscores )
					highscoreMenu->handleKeyboardInput( ev.key.keysym.sym );
				else if( currentGameState == GameState_Game_Over_Won )
					winScreen->handleKeyboardInput( ev.key.keysym.sym );
				break;
			case( SDL_MOUSEBUTTONDOWN ) :
				if( currentGameState == GameState_Paused )
					pauseMenu->mouseButtonClicked( mouseX, mouseY );
				else if( currentGameState == GameState_Game_Over )
					gameOverMenu->mouseButtonClicked( mouseX, mouseY );
				else if( currentGameState == GameState_In_Highscores )
					highscoreMenu->mouseButtonClicked( mouseX, mouseY );
				else if( currentGameState == GameState_Game_Over_Won )
					winScreen->mouseButtonClicked( mouseX, mouseY );
				break;
		}
	}
	keyState = SDL_GetKeyboardState( NULL );
	
	if( currentGameState != GameState_Paused && currentGameState != GameState_Game_Over && currentGameState != GameState_Game_Over_Won && currentGameState != GameState_In_Highscores )
	{

		updateContainer->update( deltaTime, keyState );
		physics->Step( deltaTime, *velocityIterations, *positionIterations );//update physics
		camera->update( myCar->getOriginX(), myCar->getOriginY(), deltaTime );
		for( int x = 0; x < readyTurrets.size(); x++ )
		{
			turrets.push_back( readyTurrets.at( x ) );
			drawContainer->add( readyTurrets.at( x ) );
			updateContainer->add( readyTurrets.at( x ) );
		}
		readyTurrets.clear();
	}

	if( currentGameState == GameState_Running && MissionControl::getInstance().currentMission->complete )
	{
		win();
	}	

	//update SDL
	updateSDL();
	fpsCounter->loop();
	if( currentGameState != GameState_Paused )
	{
		handleProjectileRemoveStack();
		handleCollectibleRemoveStack();
		handleBodyRemoveStack();
		handleExplosionRemoveStack();
	}
}

void World::run()
{
	setGameState( GameState_In_MainMenu );

	while( currentGameState != GameState_Closing )
	{
		tick();
	}

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
	else if( currentGameState == GameState_Game_Over )
		gameOverMenu->tick( mouseX, mouseY );
	else if( currentGameState == GameState_In_Highscores )
		highscoreMenu->tick( mouseX, mouseY );
	else if( currentGameState == GameState_Game_Over_Won )
		winScreen->tick( mouseX, mouseY );
	SDL_RenderPresent( renderTarget );
}

float World::calcDeltaTime()
{
	prevTime = currentTime;
	currentTime = SDL_GetTicks();
	deltaTime = ( currentTime - prevTime ) / 1000.0f;
	if( fastForward )
	{
		deltaTime *= 2;
	}
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

void World::handleCollectibleRemoveStack()
{
	for (size_t i = 0; i < collectibleRemoveStack->size(); i++)
	{
		updateContainer->remove(collectibleRemoveStack->at(i));
		drawContainer->remove(collectibleRemoveStack->at(i));
		delete collectibleRemoveStack->at(i);
		collectibleRemoveStack->at(i) = nullptr;
	}
	collectibleRemoveStack->clear();
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

void World::destroyCollectible(Collectible * collectible)
{
	activeCollectibles->erase(std::remove(activeCollectibles->begin(), activeCollectibles->end(), collectible), activeCollectibles->end());
	collectibleRemoveStack->push_back(collectible);
}

void World::createExplosion(SDL_Rect positionRect)
{
	Explosion* newExplosion = new Explosion(renderTarget, this, positionRect);
	explosions->push_back( newExplosion );
	updateContainer->add( newExplosion );
	drawContainer->add( newExplosion );
	sound->playSound( Sound_Explosion );
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

Uint32 World::getFPS()
{
	return fpsCounter->fps_current;
}

void World::addProjectile( Projectile *projectile )
{	
	updateContainer->add( projectile );
	drawContainer->add( projectile );
	activeProjectiles->push_back( projectile );
}

void World::addCollectible(int w, int h, int x, int y, Collectible::Collectibletypes type)
{
	Collectible* newCollectibe = new Collectible(physics, renderTarget, w, h, x, y, this, type);
	updateContainer->add(newCollectibe);
	drawContainer->add(newCollectibe);
	activeCollectibles->push_back(newCollectibe);
}


	void World::addCollidable(int w, int h, int x, int y, CollideObject::CollideType type)
{
	CollideObject* newCollectibe = new CollideObject(this, physics, renderTarget, w, h, x, y, type);
	updateContainer->add(newCollectibe);
	drawContainer->add(newCollectibe);
	activeCollideObjects->push_back(newCollectibe);
}
void World::cameraShake()
{
	camera->cameraShake( 0.10f );
}

void World::addObject(B2Content* object)
{
	objects->push_back( object );
	updateContainer->add( object );
	drawContainer->add( object );
}


bool World::chunckIsLoaded(int x, int y)
{	
	if( loadedChunks.count( coord( x, y ) ) > 0 )
	{
		return true;
	}
	return false;	
}

void World::loadChunk(int x, int y)
{
	loadedChunks[coord(x, y)] = true;
}
	

void World::gameOver()
{
	sound->pauseAllSounds();
	currentGameState = GameState_Game_Over;
	gameOverMenu->firstTick();
}

void World::showHighscores(bool newScore)
{
	sound->pauseAllSounds();
	currentGameState = GameState_In_Highscores;
	highscoreMenu->firstTick( newScore );
}

std::vector<IObjective*> World::getObjectives()
{
	vector<IObjective*> objectives = vector<IObjective*>();
	for( size_t i = 0; i < activeCollectibles->size(); i++ )
	{
		if( MissionControl::getInstance().currentMission->getCurrentObjective()->getType() == activeCollectibles->at( i )->objectiveType )
		{
			objectives.push_back( activeCollectibles->at( i ) );
		}
	}

	for( size_t i = 0; i < turrets.size(); i++ )
	{
		if( MissionControl::getInstance().currentMission->getCurrentObjective()->getType() == turrets[i]->objectiveType )
		{
			objectives.push_back( turrets[i] );
		}
	}
	return objectives;
}

void World::win()
{
	sound->pauseAllSounds();
	currentGameState = GameState_Game_Over_Won;
	winScreen->firstTick();
}