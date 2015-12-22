#pragma once
#include "SDL.h"
#include <Box2D\Box2D.h>
#include "Turret.h"
class World;
class DrawVisitor;
class UpdateVisitor;
class TDCar;

class MovingTurret : public Turret {
public:
	MovingTurret(b2World* world, SDL_Renderer* renderTarget, int xPos, int yPos, TDCar* c, World* gameWorld);
	~MovingTurret();
	void accept(UpdateVisitor *uv);
};