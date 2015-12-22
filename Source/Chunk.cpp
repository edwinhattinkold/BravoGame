#include "Chunk.h"
#include "World.h"
#include "LevelFactory.h"

Chunk::Chunk(SDL_Renderer *rt, MiniChunk miniChunk, World *world, int x, int y)
{
	
	renderTarget = rt;
	locations = new std::vector<Location>();
	//TO IMPROVE
	level = LevelFactory::getInstance()->getLevel( miniChunk.level );
	//create holder and definitions for box2d
	collisionBodyDef = new b2BodyDef();
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

	this->world->loadChunk(x, y);
}

void Chunk::addCollectable()
{
	if (!this->world->chunckIsLoaded(x, y))
	{
		//Collectibles laden

		
		int positionNewXMin = x * (1024 / 20);
		int positionNewXMax = (x + 1) * (1024 / 20);

		int positionNewYMin = y * (1024 / 20);
		int positionNewYMax = (y+1) * (1024 / 20);

		int numberRandom = Random::getInstance().nextInt(1, level->possibleCollectibles.size());

		int randomX = Random::getInstance().nextInt(positionNewXMin, positionNewXMax);
		int randomY = Random::getInstance().nextInt(positionNewYMin, positionNewYMax);

		world->addCollectible(5, 5, randomX, -randomY, level->possibleCollectibles[numberRandom - 1]);

		 numberRandom = Random::getInstance().nextInt(1, level->possibleCollide.size());
		 randomX = Random::getInstance().nextInt(positionNewXMin, positionNewXMax);
		 randomY = Random::getInstance().nextInt(positionNewYMin, positionNewYMax);
		world->addCollidable(5, 5, randomX, -randomY, level->possibleCollide[numberRandom - 1]);
		

	}
	
}

Chunk::~Chunk()
{
	

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