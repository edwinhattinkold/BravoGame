#pragma once
#include <string>
#include "Objective.h"
#include "Assets.h"
using namespace std;
class IObjective
{
private:
	bool collected;
public:
	Asset objectiveType;
	IObjective( Asset type);
	IObjective();
	~IObjective();
	void collect( Objective *objective );
};

