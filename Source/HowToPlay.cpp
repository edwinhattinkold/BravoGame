#include "HowToPlay.h"

HowToPlay::HowToPlay(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, Camera* camera, TTF_Font* font){
	this->camera = camera;
	sound = Sound::getInstance();
	sound->playSoundLooping(Sound_MainMenu_Theme, 0.50f);

	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = camera->getCamera()->w;
	backgroundImageRect.h = camera->getCamera()->h;
	this->backgroundImage = backgroundImage;
}


int HowToPlay::showMenu(SDL_Renderer* renderTarget){
	SDL_GetMouseState(&mouseX, &mouseY);
	CustomCursor::getInstance()->draw(mouseX, mouseY);
	int choice = createMenu(renderTarget);
	switch (choice){
	case(Choices::Back) :
		return Choices::Back;
		break;
	case(Choices::Exit) :
		return Choices::Exit;
	default:
		return Choices::Back;
		break;
	}
	return choice;
}