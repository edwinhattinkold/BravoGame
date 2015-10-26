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

	void Update(float deltaTime, const Uint8* keyState);
	void Add(IUpdateable *updateable);
	void Remove(IUpdateable *updateable);
};

