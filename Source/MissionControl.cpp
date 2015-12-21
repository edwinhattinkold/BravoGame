#include "MissionControl.h"

MissionControl::MissionControl()
{
	Mission *mission = new Mission( "Go be useful" );
	mission->addObjective( "Collect gasoline: ", Asset_Gasoline, 2 );
	mission->addObjective( "Shiet die boom HELEMAAL LEK OFNIEJ: ", Asset_Tree, 1 );
	mission->addObjective( "die turret moet ook kapot", Asset_Turret_Calm, 1 );
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