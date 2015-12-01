#include "Random.h"

Random& Random::getInstance()
{
	static Random    instance; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return instance;
}

int Random::nextInt( int min, int max )
{
	uniform_int_distribution<int> dist{ min, max };
	return dist( dre );
}