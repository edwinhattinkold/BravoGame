#pragma once

#include "FixtureUserData.h"
class GroundAreaFUD : FixtureUserData
{
public:
	float frictionModifier;
	bool outOfCourse;

	GroundAreaFUD(float fm, bool ooc) : FixtureUserData(FUD_GROUND_AREA) {
		frictionModifier = fm;
		outOfCourse = ooc;
	}
};

