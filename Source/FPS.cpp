#include "FPS.h"
#include <iostream>

FPS::FPS()
{
	fps_frames = 0;
	fps_lasttime = SDL_GetTicks();
}


FPS::~FPS()
{}

void FPS::loop()
{
	fps_frames++;
	if( fps_lasttime < SDL_GetTicks() - FPS_INTERVAL * 1000 )
	{
		fps_lasttime = SDL_GetTicks();
		fps_current = fps_frames;
		fps_frames = 0;
	}
}

