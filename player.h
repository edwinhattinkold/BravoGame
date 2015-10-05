#ifndef PLAYER_H
#define PLAYER_H

#include<SDL.h>
#include<string>
#include "sprite.h"

class Player : public Sprite
{
private:
	bool isActive;
	SDL_Scancode keys[4];
	float moveSpeed;

public:
	enum PlayerAnimation { Walking_Left, Walking_Up, Walking_Right, Walking_Down, PlayerAnimationsCount };
	Player(SDL_Renderer *renderTarget, int xPosition, int yPosition, float moveSpeed);
	~Player();

	virtual void Update(float delta, const Uint8 *keyState);
	void SetAnimation(PlayerAnimation playerAnimation);
};

#endif

