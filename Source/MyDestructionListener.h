#pragma once
#include <Box2D\Box2D.h>
#include "FixtureUserData.h"

class MyDestructionListener : public b2DestructionListener
{
public:
	void SayGoodbye(b2Fixture* fixture)
	{
		if (FixtureUserData* fud = (FixtureUserData*)fixture->GetUserData())
			delete fud;
	}

	//(unused but must implement all pure virtual functions)
	void SayGoodbye(b2Joint* joint) {}
};

