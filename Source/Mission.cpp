#include "Mission.h"


Mission::Mission(string title)
{
	this->title = title;
	objectives = new vector<Objective*>();
}


Mission::~Mission()
{
	for( std::vector<Objective*>::iterator it = objectives->begin(); it != objectives->end(); ++it )
	{
		delete *it; *it = nullptr;
	}
	delete objectives;
	objectives = nullptr;
}

void Mission::setObjectives( vector<Objective*> *objectives )
{
	this->objectives = objectives;
}

void Mission::addObjective( Objective *objective )
{
	this->objectives->push_back( objective );
}

void Mission::addObjective( string title, Asset type, int total )
{
	this->objectives->push_back( new Objective( title, type, total, 0));
}

Objective* Mission::getCurrentObjective()
{
	cout << objectives->at( currentObjective )->title << " \n";
	return objectives->at( currentObjective );
}

void Mission::nextObjective()
{
	if( currentObjective < objectives->size() - 1 && !complete )
	{
		cout << "next objective \n";
		currentObjective++;
	} else
	{
		cout << "Mission complete \n";
		complete = true;
	}
}

void Mission::addOne( Asset type )
{
	if( !complete )
	{
		getCurrentObjective()->addOne(type);
		if( getCurrentObjective()->completed() )
		{
			nextObjective();
		}
	}
}