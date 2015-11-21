#pragma once

#include <SDL.h>

class IUpdateable;
class Turret;

class UpdateVisitor
{
private:
	float delta;
	const Uint8 *keyState;
public:
	UpdateVisitor();
	~UpdateVisitor();
	void visit(IUpdateable *iu, float deltaTime, const Uint8 *keyState);
	void visit(Turret* turret, float deltaTime, const Uint8 *keyState);
};

