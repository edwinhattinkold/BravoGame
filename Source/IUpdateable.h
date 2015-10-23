#pragma once
class UpdateVisitor;

class IUpdateable
{
public:
	virtual void Accept(UpdateVisitor &uv, float deltaTime){};
	virtual void Update(float delta, int *keyState){};
};

