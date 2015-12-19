#include "MovingTurret.h"
#include "World.h"
#include "UpdateContainer.h"
#include "ChasingTurretState.h"
#include "TDCar.h"

MovingTurret::MovingTurret(b2World* world, SDL_Renderer* renderTarget, int xPos, int yPos, TDCar* c, World* gameWorld) 
	:Turret(world, renderTarget, xPos, yPos,  c,  gameWorld)
{
	getBody()->SetType(b2_dynamicBody);
	setState(new ChasingTurretState(this));
}

MovingTurret::~MovingTurret(){

}

void MovingTurret::accept(UpdateVisitor* uv){
	uv->visit(this);
}
