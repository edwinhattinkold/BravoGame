#include "MissionControl.h"
static MissionControl* instance;

MissionControl::MissionControl()
{
}


MissionControl::~MissionControl()
{}

MissionControl* MissionControl::getInstance()
{
	if( !instance )
		instance = new MissionControl();
	return instance;
}

void MissionControl::addOne( Asset type )
{
	currentMission->addOne( type );
}