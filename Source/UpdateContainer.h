#pragma once
#include "IUpdateable.h"
#include "UpdateVisitor.h"
#include <vector>

class UpdateContainer
{
private:
	std::vector<IUpdateable*> objects;
	UpdateVisitor *uv;
public:
	UpdateContainer();
	~UpdateContainer();
	void Add(IUpdateable *updateable);
	void Remove(IUpdateable *updateable);
	void Update(float deltaTime);
};

