#include "Chunk.h"
#include "World.h"
#include "LevelFactory.h"


SDL_Texture* loadImage( SDL_Renderer *renderTarget, std::string filePath )
{
	filePath = filePath.substr( 3 );
	SDL_Surface *surface = IMG_Load( filePath.c_str() );
	if( surface == NULL )
		std::cout << "Error1" << filePath << std::endl;
	else
	{
		SDL_Texture *texture = SDL_CreateTextureFromSurface( renderTarget, surface );
		if( texture == NULL )
			std::cout << "Error2" << std::endl;
		SDL_FreeSurface( surface );
		return texture;
	}
	return NULL;
}

Chunk::Chunk(SDL_Renderer *rt, MiniChunk miniChunk, World *world, int x, int y)
{
	
	renderTarget = rt;
	textures = new std::vector<SDL_Texture*>();
	locations = new std::vector<Location>();
	//TO IMPROVE
	level = LevelFactory::getInstance()->getLevel( miniChunk.level );
	//create holder and definitions for box2d
	bodies = new std::vector<b2Body*>();
	collisionBodyDef = new b2BodyDef();
	//collectibleItems = new std::vector<Collectible*>();
	collisionBodyDef->type = b2_staticBody;
	collisionBodyDef->angle = 0;
	collisionFixtureDef = new b2FixtureDef();
	boxShape = new b2PolygonShape();
	boxShape->SetAsBox( 1, 1 );
	collisionFixtureDef->shape = boxShape;
	collisionFixtureDef->density = 1;
	XMLReader reader;
	reader.parseXMLFile( this, "maps/" + miniChunk.tmx );
	this->x = x;
	this->y = y;
	this->world = world;
	
	addCollectable();
}

void Chunk::addCollectable()
{
	//Collectibles laden
	std::cout << "x: " << x << " y: " << y << endl;
	

	int positonNewX = x * (1024 / 20);
	int positionNewY = y * (1024 / 20);

	int numberRandom = Random::getInstance().nextInt(1, level->possibleCollectibles.size());
	
	Collectible* collectible = world->addCollectible(5, 5, positonNewX, -positionNewY, level->possibleCollectibles[numberRandom - 1]);
	collectibleItems.push_back(collectible);
}

Chunk::~Chunk()
{
	for( size_t j = 0; j < textures->size(); j++ )
	{
		SDL_DestroyTexture( textures->at( j ) );
		textures->at( j ) = nullptr;
	}
	/* TODO Objecten verwijderen uit de map */
	for (size_t k = 0; k < bodies->size(); k++){
		//world->destroyBody(bodies->at(k));
		//bodies->at(k) = nullptr;
	}
	for (size_t i = 0; i < collectibleItems.size(); i++)
	{
		world->destroyCollectible(collectibleItems.at(i));
		delete collectibleItems.at(i);
		collectibleItems.at(i) = nullptr;
		
	}

	delete bodies;
	bodies = nullptr;
	delete textures;
	textures = nullptr;
	delete locations;
	locations = nullptr;
	/*delete bodies;*/
	delete collisionBodyDef;
	collisionBodyDef = nullptr;
	delete collisionFixtureDef;
	collisionFixtureDef = nullptr;
	delete boxShape;
	boxShape = nullptr;
}

void Chunk::addTileSet()
{
}

void Chunk::addCollidableObject( int x, int y )
{
	collisionBodyDef->position.Set(x * 2, y * 3);
	//b2Body *staticBody = world->createBody(collisionBodyDef);
	//staticBody->CreateFixture(collisionFixtureDef);
	//bodies->push_back(staticBody);
}

void Chunk::addLocation( Location l )
{
	locations->push_back( l );
}

void Chunk::draw(SDL_Rect *cameraRect )
{
	Tile *tile = nullptr;
	SDL_Rect tarRect = { 0, 0, 32, 32 };
	for( size_t i = 0; i < locations->size(); i++ )
	{
		Location l = locations->at( i );
		tarRect.x = l.x * 32 + (x*1024) - cameraRect->x;
		tarRect.y = l.y * 32 + (y*1024) - cameraRect->y;
		tile = level->tiles->at( l.id );;
		SDL_RenderCopy( renderTarget, tile->getTexture(), tile->getRect(), &tarRect );
	}
}