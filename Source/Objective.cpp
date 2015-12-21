#include "Objective.h"

Objective::Objective( string title, string type, int total, int collected )
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

void Objective::addOne( string type )
{
	if( this->type.compare( type ) == 0 && collected < total)
	{
		collected++;
	} else if( this->type.compare( type ) == 0 )
	{
		cout << "DONE \n";
	}
}
