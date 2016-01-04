#include "MissionControl.h"

MissionControl::MissionControl()
{
	Mission *mission = new Mission( "Go be useful" );
	mission->addObjective( "Collect gasoline tanks ", Asset_Gasoline, 2 );
	mission->addObjective( "Kill a tree ", Asset_Tree, 1 );
	mission->addObjective( "Fuck that turret up ", Asset_Turret_Calm, 1 );
	currentMission = mission;
}


MissionControl::~MissionControl()
{
	if( currentMission != nullptr )
	{
		delete currentMission;
		currentMission = nullptr;
	}
}

MissionControl& MissionControl::getInstance()
{
	static MissionControl    instance;	// Guaranteed to be destroyed.
										// Instantiated on first use.
	return instance;
}

void MissionControl::addOne( Asset type )
{
	currentMission->addOne( type );
}

string MissionControl::getCurrentMissionTitle()
{
	return currentMission->title;
}

string MissionControl::getCurrentObjectiveTitle()
{
	return currentMission->getCurrentObjective()->title;
}

string MissionControl::getCurrentObjectiveProgress()
{
	return currentMission->getCurrentObjective()->getProgress();
}