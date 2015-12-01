#pragma once
#include "SDL.h"
class FPS
{
private:
	#define FPS_INTERVAL 1.0 //seconds.

	Uint32 fps_lasttime;//the last recorded time.
	Uint32 fps_frames;	//frames passed since the last recorded fps.
public:
	Uint32 fps_current;	//the current FPS.
	FPS();
	~FPS();
	void loop();
};

