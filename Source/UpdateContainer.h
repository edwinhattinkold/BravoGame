#pragma once
#include "IUpdateable.h"
#include "UpdateVisitor.h"
#include <vector>

class UpdateContainer
{
private:
	std::vector<IUpdateable*> *objects;
	UpdateVisitor *uv;
public:
	UpdateContainer();
	~UpdateContainer();

	void update(float deltaTime, const Uint8* keyState);
	void add(IUpdateable *updateable);
	void remove(IUpdateable *updateable);
};

