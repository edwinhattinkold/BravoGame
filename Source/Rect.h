#pragma once
#include "IDrawable.h"
#include "IUpdateable.h"
class Rect :
	public IDrawable
{
private:
	SDL_Rect *rect;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
public:
	Rect( int x, int y, int width, int height, Uint8 r = 255, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255 );
	~Rect();

	void setColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	
	virtual void accept( DrawVisitor *dv );

	virtual void draw( SDL_Renderer *renderTarget);

};

