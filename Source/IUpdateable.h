#pragma once
#include <iostream>
#include <SDL.h>
class UpdateVisitor;

class IUpdateable
{
public:
	virtual void Accept(UpdateVisitor *uv, float deltaTime, const Uint8 *keyState);
	virtual void Update(float delta, const Uint8 *keyState);
};

