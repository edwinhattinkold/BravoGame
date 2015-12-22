#include "IObjective.h"


IObjective::IObjective(Asset type)
{
	objectiveType = type;
	collected = false;
}

IObjective::IObjective()
{
	collected = false;
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