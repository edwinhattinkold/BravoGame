#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Objective.h"
#include "Assets.h"
using namespace std;
class Mission
{
private:
	vector<Objective*> *objectives;
	int currentObjective = 0;
public:
	string title;
	bool complete = false;
	Mission( string title);
	~Mission();
	void setObjectives( vector<Objective*> *objectives );
	void addObjective( string title, Asset type, int total );
	void addObjective( Objective *objective );
	Objective* getCurrentObjective();
	void nextObjective();
	void addOne( Asset type );
	void reset();
};