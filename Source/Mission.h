#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Objective.h"
using namespace std;
class Mission
{
private:
	string title;
	vector<Objective*> *objectives;
	int currentObjective = 0;
public:
	bool complete = false;
	Mission( string title);
	~Mission();
	void setObjectives( vector<Objective*> *objectives );
	void addObjective( string title, string type, int total );
	void addObjective( Objective *objective );
	Objective* getCurrentObjective();
	void nextObjective();
	void addOne( string type );
};