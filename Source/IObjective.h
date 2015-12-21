#pragma once
#include <string>;
#include "Objective.h"
using namespace std;
class IObjective
{
private:
	bool collected;
public:
	string objectiveType;
	IObjective( string type);
	IObjective();
	~IObjective();
	void collect( Objective *objective );
};

