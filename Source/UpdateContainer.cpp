#include "UpdateContainer.h"


UpdateContainer::UpdateContainer()
{
	uv = new UpdateVisitor();
	objects = {};
}


UpdateContainer::~UpdateContainer()
{
	//TODO: Delete each IUpdateable since it's on the heap
	delete uv;
}

void UpdateContainer::Add(IUpdateable *updateable)
{
	this->objects.push_back(updateable);
}

void UpdateContainer::Remove(IUpdateable *updateable)
{
	std::vector<IUpdateable *>::iterator it;
	it = std::find(objects.begin(), objects.end(), updateable);

	// swap the one to be removed with the last element
	// and remove the item at the end of the container
	std::swap(*it, objects.back());
	delete updateable;
	objects.pop_back();
}

void UpdateContainer::Update(float deltaTime)
{
	for (int c = 0; c < this->objects.size(); c++){
		this->objects[c]->Accept(*uv, deltaTime);
	}
}
