#pragma once
#include "Player.h"
class UpdateVisitor
{
private:
	float delta;
	const Uint8 *keyState;
public:
	UpdateVisitor();
	~UpdateVisitor();
	void visit(Player *p, float deltaTime);
};

