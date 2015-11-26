#pragma once

#include <SDL.h>

class IUpdateable;
class TDCar;
class MapDrawer;
class Projectile;

class UpdateVisitor
{
private:
	float deltaTime;
	const Uint8 *keyState;
public:
	UpdateVisitor();
	~UpdateVisitor();
	void setDelta( float deltaTime );
	void setKeyState( const Uint8 *keyState );

	/* Visit methods */
	void visit( IUpdateable *iu );
	void visit( TDCar *car );
	void visit( MapDrawer *md );
	void visit( Projectile *projectile );
};

