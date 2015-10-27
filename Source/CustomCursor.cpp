#include "CustomCursor.h"
static CustomCursor* instance;

CustomCursor::CustomCursor()
{

}

CustomCursor::~CustomCursor()
{
	SDL_DestroyTexture( image ); 
	image = nullptr;
}

/* Singleton */
CustomCursor* CustomCursor::getInstance()
{
	if( !instance )
		instance = new CustomCursor();
	return instance;
}

void CustomCursor::setRenderTarget( SDL_Renderer* renderTarget )
{
	this->renderTarget = renderTarget;
	this->renderTarget = renderTarget;
	SDL_Surface *surface = IMG_Load( "Images/Cursor/customCursor.png" );
	if( surface == NULL )
		std::cout << "Error" << std::endl;
	else
	{
		image = SDL_CreateTextureFromSurface( renderTarget, surface );
		if( image == NULL )
			std::cout << "Error" << std::endl;
	}
	SDL_FreeSurface( surface );

	SDL_QueryTexture( image, NULL, NULL, &positionRect.w, &positionRect.h );
}

void CustomCursor::draw( int mouseXPosition, int mouseYPosition)
{
	positionRect.x = mouseXPosition;
	positionRect.y = mouseYPosition;
	SDL_RenderCopy( renderTarget, image, NULL, &positionRect );
}

extern __declspec(dllexport) void CustomCursor_Quit()
{
	delete instance; instance = nullptr;
}
