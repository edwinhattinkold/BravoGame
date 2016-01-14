#include "MissionControl.h"

MissionControl::MissionControl()
{
	Mission *mission = new Mission( "Go be useful " );
	mission->addObjective( "Collect gasoline tanks ", Asset_Gasoline, 2 );
	mission->addObjective( "Collect health packs ", Asset_Health, 2 );
	mission->addObjective( "Collect more gasoline tanks ", Asset_Gasoline, 2 );
	mission->addObjective( "Collect carparts ", Asset_Collectible, 2 );
	mission->addObjective( "Collect even more gasoline tanks ", Asset_Gasoline, 2 );
	mission->addObjective( "Destroy turrets ", Asset_Turret_Calm, 2 );
	mission->addObjective( "Triple A gameplay: more gasoline tanks please ", Asset_Gasoline, 2 );
	mission->addObjective( "Kill a tree ", Asset_Tree, 1 );
	mission->addObjective( "Destroy all the turrets ", Asset_Turret_Calm, 20 );
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

Asset MissionControl::getObjectiveType()
{
	return currentMission->getCurrentObjective()->getType();
}

void MissionControl::reset()
{
	currentMission->reset();
}