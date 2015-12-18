#pragma once
#include "BaseLevel.h"
class LevelSnow :
	public BaseLevel
{
public:
	LevelSnow();
	~LevelSnow();
	void startSound();
	void stopSound();
};

