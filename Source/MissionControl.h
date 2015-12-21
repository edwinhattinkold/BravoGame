#pragma once
#include <vector>
#include "Mission.h"
using namespace std;
class MissionControl
{
private:

	MissionControl();
	MissionControl( MissionControl const& );
	void operator=( MissionControl const& );
public:
	/* Singleton */
	static MissionControl* getInstance();
	~MissionControl();

	Mission *currentMission;

	void addOne( string type );
};