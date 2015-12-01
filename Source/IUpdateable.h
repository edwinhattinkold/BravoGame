#pragma once
#include <iostream>
#include <SDL.h>
class UpdateVisitor;

class IUpdateable
{
public:
	virtual void accept( UpdateVisitor *uv );
	virtual void update(float delta, const Uint8 *keyState);
};

