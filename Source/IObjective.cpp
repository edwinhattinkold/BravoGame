#include "IObjective.h"


IObjective::IObjective(Asset type)
{
	objectiveType = type;
	collected = false;
	x = 0;
	y = 0;
}

IObjective::IObjective()
{
	collected = false;
	x = 0;
	y = 0;
}



IObjective::~IObjective()
{}

void IObjective::collect( Objective *objective )
{
	if( !collected )
	{
		collected = true;
		objective->addOne( objectiveType );
	}
}