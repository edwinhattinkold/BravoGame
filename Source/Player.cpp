#include "Player.h"
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include "UpdateVisitor.h"

Player::Player(SDL_Renderer *renderTarget, int xPosition, int yPosition, float moveSpeed, DrawContainer *dc)
	:Sprite(xPosition, yPosition, dc)
{
	float animSpeed = 0.10f;
	/* Create all the animations required for this sprite */

	Animation* walking_left_animation = new Animation(renderTarget, "Images/Animations/Walking/walking_left.png", 3, 1, 1, 0, animSpeed);
	Animation* walking_up_animation = new Animation(renderTarget, "Images/Animations/Walking/walking_up.png", 3, 1, 1, 0, animSpeed);
	Animation* walking_right_animation = new Animation(renderTarget, "Images/Animations/Walking/walking_right.png", 3, 1, 1, 0, animSpeed);
	Animation* walking_down_animation = new Animation(renderTarget, "Images/Animations/Walking/walking_down.png", 3, 1, 1, 0, animSpeed);

	/* Has to be in order of the enum */
	animations = new std::vector<Animation*>();
	animations->push_back(walking_left_animation);
	animations->push_back(walking_up_animation);
	animations->push_back(walking_right_animation);
	animations->push_back(walking_down_animation);

	/* Set the animation */
	SetAnimation(Walking_Down);

	this->moveSpeed = moveSpeed;
	isActive = false;

	static int playerNumber = 0;
	playerNumber++;

	if (playerNumber == 1){
		keys[0] = SDL_SCANCODE_W;
		keys[1] = SDL_SCANCODE_S;
		keys[2] = SDL_SCANCODE_A;
		keys[3] = SDL_SCANCODE_D;
	}
	else {
		keys[0] = SDL_SCANCODE_UP;
		keys[1] = SDL_SCANCODE_DOWN;
		keys[2] = SDL_SCANCODE_LEFT;
		keys[3] = SDL_SCANCODE_RIGHT;
	}
}


Player::~Player()
{

}

//TODO: animation based on X and Y velocity
void Player::Update(float delta, const Uint8 *keyState){
	isActive = true;
	if (keyState[keys[0]])
	{
		SetAnimation(Walking_Up);
		positionRect.y -= int(moveSpeed * delta);
	}
	else if (keyState[keys[1]]){
		SetAnimation(Walking_Down);
		positionRect.y += int(moveSpeed * delta);
	}
	else if (keyState[keys[2]]){
		SetAnimation(Walking_Left);
		positionRect.x -= int(moveSpeed * delta);
	}
	else if (keyState[keys[3]]){
		SetAnimation(Walking_Right);
		positionRect.x += int(moveSpeed * delta);
	}
	else
		isActive = false;

	if (isActive)
		animations->at(currentAnimaton)->Update(delta);
	else
		animations->at(currentAnimaton)->StandStill();
}

void Player::SetAnimation(PlayerAnimation playerAnimation){
	currentAnimaton = playerAnimation;

	Animation* anim = animations->at(currentAnimaton);

	originX =			anim->getOriginX();
	originY =			anim->getOriginY();
	positionRect.w =	anim->getFrameWidth();
	positionRect.h =	anim->getFrameHeight();
}
