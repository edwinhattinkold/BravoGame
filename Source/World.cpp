#include "World.h"
#include "CustomCursor.h"
#include "Assets.h"
#include "HighscoreMenu.h"

World::World( SDL_Window *window, int levelWidth, int levelHeight, TTF_Font* font )
{
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

	//create add and remove stacks
	bodyRemoveStack = new std::vector<B2Content*>();
	projectileRemoveStack = new std::vector<Projectile*>();
	explosionRemoveStack = new std::vector<Explosion*>();
	activeProjectiles = new std::vector<Projectile*>();
	explosions = new std::vector<Explosion*>();
	objects = new std::vector<B2Content*>();

	collectibleRemoveStack = new std::vector<Collectible*>();
	activeCollectibles = new std::vector<Collectible*>();

	//create physics world (box2d)
	gravity = new b2Vec2( 0.0f, 0.0f );
	physics = new b2World( *gravity );

	//Create containers
	drawContainer = new DrawContainer( renderTarget, camera->getCamera() );
	updateContainer = new UpdateContainer();

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

	//add car
	myCar = new TDCar( this, physics, renderTarget, camera, 3, 6 );
	drawContainer->add( myCar );
	updateContainer->add( myCar );

	//add objects ( no special destructor )
	addObject( new Tree( this, physics, renderTarget, 10, 10, 20, -15 ) );
	addObject( new Tree( this, physics, renderTarget, 10, 10, 40, -30 ) );

	//add objects ( own destructor )
	myTurret = new Turret( physics, renderTarget, 50, -40, myCar, this );
	drawContainer->add( myTurret );
	updateContainer->add( myTurret );

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
	delete hud;										hud = nullptr;
}

void World::reset()
{
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

/*
	Voer een actie uit op de auto op basis
	van myType
*/
void World::destroyCollectible(Collectible * collectible)
{
	switch (collectible->myType)
	{
	case Collectible::Collectibletypes::Nitro:
			myCar->hitNitro(5.0f);
			break;
	case Collectible::Collectibletypes::Oil:
		myCar->hitOil(2.0f);
		break;
	case Collectible::Collectibletypes::Gasoline:
		myCar->addGasoline(4.0f);
		break;
	}
	activeCollectibles->erase(std::remove(activeCollectibles->begin(), activeCollectibles->end(), collectible), activeCollectibles->end());
	collectibleRemoveStack->push_back(collectible);
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
	Collectible * newCollectibe = new Collectible(physics, renderTarget, w, h, x, y, this, type);
	updateContainer->add(newCollectibe);
	drawContainer->add(newCollectibe);
	activeCollectibles->push_back(newCollectibe);
}

void World::addObject(B2Content* object)
{
	objects->push_back( object );
	updateContainer->add( object );
	drawContainer->add( object );
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

	if( MissionControl::getInstance().currentMission->getCurrentObjective()->getType() == myTurret->objectiveType )
	{
		objectives.push_back( myTurret );
	}
	return objectives;
}

void World::win()
{
	sound->pauseAllSounds();
	currentGameState = GameState_Game_Over_Won;
	winScreen->firstTick();
}