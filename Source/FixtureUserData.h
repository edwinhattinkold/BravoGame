#pragma once

//types of fixture user data
enum fixtureUserDataType {
	FUD_CAR_TIRE,
	FUD_GROUND_AREA
};

//a class to allow subclassing of different fixture user data
class FixtureUserData {
	fixtureUserDataType m_type;
protected:
	FixtureUserData(fixtureUserDataType type) : m_type(type) {}
public:
	virtual fixtureUserDataType getType() { return m_type; }
	virtual ~FixtureUserData() {}
};

