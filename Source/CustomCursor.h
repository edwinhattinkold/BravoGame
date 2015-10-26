#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include <iostream>

class CustomCursor
{
private:
	SDL_Rect positionRect;
	SDL_Texture *image;
	SDL_Renderer *renderTarget;

	/* Singleton */
	CustomCursor(SDL_Renderer);
	CustomCursor( CustomCursor const& );
	void operator=(CustomCursor const&);

public:
	/* Singleton */
	static CustomCursor* getInstance();

	CustomCursor( );
	~CustomCursor();

	void setRenderTarget( SDL_Renderer* renderTarget );

	void draw( int mouseXPosition, int mouseYPosition );
};

extern __declspec(dllexport) void Cursor_Quit();

