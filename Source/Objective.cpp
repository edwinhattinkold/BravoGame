#include "Objective.h"

Objective::Objective( string title, Asset type, int total, int collected )
{
	this->title = title;
	this->type = type;
	this->total = total;
	this->collected = collected;
}


Objective::~Objective()
{}

bool Objective::completed()
{
	return total <= collected;
}

void Objective::addOne( Asset type )
{
	if( this->type == type && collected < total)
	{
		collected++;
	} else if( this->type == type )
	{
		cout << "DONE \n";
	}
}

string Objective::getProgress()
{
	return to_string( collected ).append( " of " ).append( to_string( total ) );
}

Asset Objective::getType()
{
	return type;
}

void Objective::reset()
{
	collected = 0;
}