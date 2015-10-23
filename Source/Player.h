#ifndef PLAYER_H
#define PLAYER_H

#include<SDL.h>
#include<string>
#include "IUpdateable.h"
#include "Sprite.h"
#include "DrawContainer.h"
class UpdateVisitor;

class Player : public Sprite, IUpdateable
{
private:
	bool isActive;
	SDL_Scancode keys[4];
	float moveSpeed;

public:
	enum PlayerAnimation { Walking_Left, Walking_Up, Walking_Right, Walking_Down, PlayerAnimationsCount };
	Player(SDL_Renderer *renderTarget, int xPosition, int yPosition, float moveSpeed, DrawContainer *dc);
	~Player();

	virtual void Update(float delta, const Uint8 *keyState);
	void SetAnimation(PlayerAnimation playerAnimation);

	virtual void Accept(UpdateVisitor uv, float deltaTime);

};

#endif

