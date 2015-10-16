#include "Tile.h"


Tile::Tile(SDL_Texture *texture, SDL_Rect cropRect)
{
	_texture = texture;
	_cropRect = cropRect;
}


Tile::~Tile()
{
}

SDL_Rect* Tile::getRect(){
	return &_cropRect;
}

SDL_Texture* Tile::getTexture(){
	return _texture;
}
