#pragma once

#include <SDL.h>

class IUpdateable;

class UpdateVisitor
{
private:
	float delta;
	const Uint8 *keyState;
public:
	UpdateVisitor();
	~UpdateVisitor();
	void visit(IUpdateable *iu, float deltaTime, const Uint8 *keyState);
};

