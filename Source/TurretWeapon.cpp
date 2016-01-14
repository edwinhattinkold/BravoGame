#include "TurretWeapon.h"
#include "Turret.h"
TurretWeapon::TurretWeapon(World* world, Turret* host, b2World* physics_world, SDL_Renderer * renderTarget, float fireRate, float spread)
: Weapon(world, host, physics_world, renderTarget, fireRate, spread)
{
	turret = host;
	Projectile* p = new Projectile( world, physics_world, renderTarget, Asset_MachineGun_Bullet, 50, 80 );
	p->prototype = true;
	p->muzzleFlash = Assets::getInstance()->getAsset(Asset_MuzzleFlash_Turret);
	setAmmo(p);
}


TurretWeapon::~TurretWeapon()
{

}

void TurretWeapon::fire(){
	sound->playSound( Sound_Shooting_Machine_Gun );
	Projectile* newProjectile = ammo->clone();

	//b2Vec2 direction = host->getB2DDirectionalVector();
	b2Vec2 direction;
	direction.y = cos(turret->turretAngle * DEGTORAD);
	direction.x = sin(turret->turretAngle * DEGTORAD);
	direction.Normalize();
	int randomSpread = Random::getInstance().nextInt(0 - (spread / 2), 0 + (spread / 2));
	float spreadFloat = 0.02f * randomSpread;
	direction.x += spreadFloat;
	direction.y += spreadFloat;
	direction.Normalize();

	newProjectile->setB2DPosition(host->m_body->GetWorldPoint(b2Vec2{ 0, 4 }));
	newProjectile->setDirection(direction);
	newProjectile->applyB2DAngle(host->m_body->GetAngle());

	world->addProjectile(newProjectile);
}