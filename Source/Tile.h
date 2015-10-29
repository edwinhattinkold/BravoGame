#pragma once
#include "SDL.h"

class Tile
{
private:
	SDL_Rect _cropRect;
	SDL_Texture *_texture;
public:
	
	Tile(SDL_Texture *texture, SDL_Rect cropRect);
	~Tile();
	SDL_Rect* getRect();
	SDL_Texture* getTexture();
};

