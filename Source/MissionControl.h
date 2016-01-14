#pragma once
#include <vector>
#include "Mission.h"
#include "Assets.h"
using namespace std;
class MissionControl
{
private:

	MissionControl();
	MissionControl( MissionControl const& );
	void operator=( MissionControl const& );
public:
	/* Singleton */
	static MissionControl& getInstance();
	~MissionControl();

	Mission *currentMission;

	void addOne( Asset type );
	string getCurrentMissionTitle();
	string getCurrentObjectiveTitle();
	string getCurrentObjectiveProgress();
	void reset();
	Asset getObjectiveType();
};