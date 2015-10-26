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
	this->animations = new std::vector<Animation*>();
	this->animations->push_back(walking_left_animation);
	this->animations->push_back(walking_up_animation);
	this->animations->push_back(walking_right_animation);
	this->animations->push_back(walking_down_animation);

	/* Set the animation */
	this->SetAnimation(Walking_Down);

	this->moveSpeed = moveSpeed;
	this->isActive = false;

	static int playerNumber = 0;
	playerNumber++;

	if (playerNumber == 1){
		this->keys[0] = SDL_SCANCODE_W;
		this->keys[1] = SDL_SCANCODE_S;
		this->keys[2] = SDL_SCANCODE_A;
		this->keys[3] = SDL_SCANCODE_D;
	}
	else {
		this->keys[0] = SDL_SCANCODE_UP;
		this->keys[1] = SDL_SCANCODE_DOWN;
		this->keys[2] = SDL_SCANCODE_LEFT;
		this->keys[3] = SDL_SCANCODE_RIGHT;
	}
}


Player::~Player()
{

}

//TODO: animation based on X and Y velocity
void Player::Update(float delta, const Uint8 *keyState){
	this->isActive = true;
	if (keyState[keys[0]])
	{
		this->SetAnimation(Walking_Up);
		this->positionRect.y -= int(moveSpeed * delta);
	}
	else if (keyState[keys[1]]){
		this->SetAnimation(Walking_Down);
		this->positionRect.y += int(moveSpeed * delta);
	}
	else if (keyState[keys[2]]){
		this->SetAnimation(Walking_Left);
		this->positionRect.x -= int(moveSpeed * delta);
	}
	else if (keyState[keys[3]]){
		this->SetAnimation(Walking_Right);
		this->positionRect.x += int(moveSpeed * delta);
	}
	else
		this->isActive = false;

	if (this->isActive)
		this->animations->at(currentAnimaton)->Update(delta);
	else
		this->animations->at(currentAnimaton)->StandStill();
}

void Player::SetAnimation(PlayerAnimation playerAnimation){
	this->currentAnimaton = playerAnimation;

	Animation* anim = this->animations->at(this->currentAnimaton);

	this->originX =			anim->getOriginX();
	this->originY =			anim->getOriginY();
	this->positionRect.w =	anim->getFrameWidth();
	this->positionRect.h =	anim->getFrameHeight();
}
