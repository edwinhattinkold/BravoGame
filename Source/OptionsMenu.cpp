#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, SDL_Rect* cameraRect, TTF_Font* font)
{
	this->cameraRect = cameraRect;
	sound = Sound::getInstance();
	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = cameraRect->w;
	backgroundImageRect.h = cameraRect->h;
	this->backgroundImage = backgroundImage;

	margin = 40;
	combinedHeight = 0;

	menuItems = new std::vector<MenuItem*>();
	menuItems->push_back(new MenuItem(renderTarget, font, "Sound on"));
	menuItems->push_back(new MenuItem(renderTarget, font, "Back"));

	for (std::vector<int>::size_type i = menuItems->size() - 1; i != (std::vector<int>::size_type) - 1; i--) {
		combinedHeight += menuItems->at(i)->getHeight();
		int xPosition = (cameraRect->w / 2) - (menuItems->at(i)->getWidth() / 2) - cameraRect->x;
		menuItems->at(i)->setXPosition(xPosition);
	}

	int marginHeight = ((menuItems->size() - 1) * margin);
	combinedHeight += marginHeight;

	center();
	soundMuted = false;
}

OptionsMenu::~OptionsMenu()
{
	for (size_t c = 0; c < menuItems->size(); c++)
		delete menuItems->at(c);
	delete menuItems;
}

int OptionsMenu::getBackCode(){
	return Choices::Back;
}

int OptionsMenu::getExitCode(){
	return Choices::Exit;
}

int OptionsMenu::showMenu(SDL_Renderer* renderTarget){
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

int OptionsMenu::createMenu(SDL_Renderer* renderTarget){
	SDL_Event event;
	while (1)
	{
		time = SDL_GetTicks();
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_QUIT:
				return Choices::Exit;
			case SDL_MOUSEMOTION:
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				for (size_t i = 0; i < menuItems->size(); i++)
					if (menuItems->at(i)->checkHover(mouseX, mouseY))
						sound->playSound(Sound_MainMenu_Tick);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				for (size_t index = 0; index < menuItems->size(); index++)
					if (mouseX >= menuItems->at(index)->getXPosition() && mouseX <= menuItems->at(index)->getXPosition() + menuItems->at(index)->getWidth() &&
						mouseY >= menuItems->at(index)->getYPosition() && mouseY <= menuItems->at(index)->getYPosition() + menuItems->at(index)->getHeight()){
						sound->playSound(Sound_MainMenu_Click);
						
						if (index == Choices::Sound_On_Off)
							toggleSound(renderTarget);
						else
							return index;
					}

				break;
			}
		}
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, backgroundImage, NULL, NULL);
		draw(renderTarget);
		SDL_RenderPresent(renderTarget);
	}
}

void OptionsMenu::draw(SDL_Renderer* renderTarget){
	for (std::vector<int>::size_type j = menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		menuItems->at(j)->draw(renderTarget);
	}
}

void OptionsMenu::toggleSound(SDL_Renderer* renderTarget){
	if (soundMuted){
		sound->unmute();
		soundMuted = false;
		menuItems->at(Choices::Sound_On_Off)->setText(renderTarget, "Sound On");
	}
	else{
		sound->mute();
		soundMuted = true;
		menuItems->at(Choices::Sound_On_Off)->setText(renderTarget, "Sound Off");
	}
	center();
}

void OptionsMenu::center(){
	for (std::vector<int>::size_type j = menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		int xPosition = (cameraRect->w / 2) - (menuItems->at(j)->getWidth() / 2) - cameraRect->x;
		menuItems->at(j)->setXPosition(xPosition);

		int previousHeight = 0;
		for (size_t h = 0; h < j; h++)
			previousHeight += menuItems->at(h)->getHeight();
		int yPosition = (cameraRect->h / 2) - cameraRect->y - (combinedHeight / 2) + (j * margin) + previousHeight;
		menuItems->at(j)->setYPosition(yPosition);
	}
}
