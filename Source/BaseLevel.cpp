#include "BaseLevel.h"
#include "Assets.h"

BaseLevel::BaseLevel(Asset assetId,string name)
{
	this->name = name;
	textureId = assetId;
	tiles = new std::vector<Tile*>();
	possibleCollectibles = std::vector < Collectible::Collectibletypes >() ;
	tiles->push_back( nullptr );
	addTileSet();	
}


BaseLevel::~BaseLevel()
{
	for( size_t i = 1; i < tiles->size(); i++ )
	{
		delete tiles->at( i );
		tiles->at( i ) = nullptr;
	}
	delete tiles;
	tiles = nullptr;
}

void BaseLevel::addTileSet()
{

	SDL_Texture  *texture = Assets::getInstance()->getAsset( textureId );
	//save pointer for removing
	//textures->push_back( texture );
	int x = 0;
	int y = 0;
	for( int c = 0; c < amount; c++ )
	{
		SDL_Rect cropRect;
		cropRect.h = 32;
		cropRect.w = 32;
		cropRect.x = x;
		cropRect.y = y;
		x += spacing + 32;

		tiles->push_back( new Tile( texture, cropRect ) );
		if( x + 32 > width )
		{
			x = 0;
			y += spacing + 32;
		}
	}
}

void BaseLevel::startSound()
{
}

string BaseLevel::getName()
{
	return name;
}

void BaseLevel::stopSound()
{
}
