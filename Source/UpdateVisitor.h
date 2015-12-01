#pragma once

#include <SDL.h>

class IUpdateable;
class Turret;
class TDCar;
class MapDrawer;
class Projectile;
class Explosion;
class Tree;

class UpdateVisitor
{
private:
	float deltaTime;
	const Uint8 *keyState;
public:
	UpdateVisitor();
	~UpdateVisitor();
	void visit(IUpdateable *iu, float deltaTime, const Uint8 *keyState);
	void visit(Turret* turret);
	void setDelta( float deltaTime );
	void setKeyState( const Uint8 *keyState );

	/* Visit methods */
	void visit( IUpdateable *iu );
	void visit( TDCar *car );
	void visit( MapDrawer *md );
	void visit( Projectile *projectile );
	void visit( Explosion *explosion );
	void visit( Tree *tree );
};

