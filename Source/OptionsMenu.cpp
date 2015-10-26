#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, SDL_Rect* cameraRect, TTF_Font* font)
{
	this->cameraRect = cameraRect;
	this->sound = Sound::getInstance();
	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = cameraRect->w;
	backgroundImageRect.h = cameraRect->h;
	this->backgroundImage = backgroundImage;

	this->margin = 40;
	this->combinedHeight = 0;

	this->menuItems = new std::vector<MenuItem*>();
	this->menuItems->push_back(new MenuItem(renderTarget, font, "Sound on"));
	this->menuItems->push_back(new MenuItem(renderTarget, font, "Back"));

	for (std::vector<int>::size_type i = this->menuItems->size() - 1; i != (std::vector<int>::size_type) - 1; i--) {
		this->combinedHeight += this->menuItems->at(i)->getHeight();
		int xPosition = (cameraRect->w / 2) - (this->menuItems->at(i)->getWidth() / 2) - cameraRect->x;
		this->menuItems->at(i)->setXPosition(xPosition);
	}

	int marginHeight = ((this->menuItems->size() - 1) * margin);
	combinedHeight += marginHeight;

	this->center();
	this->soundMuted = false;
}

OptionsMenu::~OptionsMenu()
{
	for (size_t c = 0; c < this->menuItems->size(); c++)
		delete this->menuItems->at(c);
	delete this->menuItems;
}

int OptionsMenu::getBackCode(){
	return Choices::Back;
}

int OptionsMenu::getExitCode(){
	return Choices::Exit;
}

int OptionsMenu::showMenu(SDL_Renderer* renderTarget){
	int choice = this->createMenu(renderTarget);
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
		this->time = SDL_GetTicks();
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_QUIT:
				return Choices::Exit;
			case SDL_MOUSEMOTION:
				this->mouseX = event.motion.x;
				this->mouseY = event.motion.y;
				for (size_t i = 0; i < this->menuItems->size(); i++)
					if (this->menuItems->at(i)->checkHover(this->mouseX, this->mouseY))
						this->sound->playSound(Sound_MainMenu_Tick);
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->mouseX = event.motion.x;
				this->mouseY = event.motion.y;
				for (size_t index = 0; index < this->menuItems->size(); index++)
					if (mouseX >= this->menuItems->at(index)->getXPosition() && mouseX <= this->menuItems->at(index)->getXPosition() + this->menuItems->at(index)->getWidth() &&
						mouseY >= this->menuItems->at(index)->getYPosition() && mouseY <= this->menuItems->at(index)->getYPosition() + this->menuItems->at(index)->getHeight()){
						this->sound->playSound(Sound_MainMenu_Click);
						
						if (index == Choices::Sound_On_Off)
							this->toggleSound(renderTarget);
						else
							return index;
					}

				break;
			}
		}
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, this->backgroundImage, NULL, NULL);
		this->draw(renderTarget);
		SDL_RenderPresent(renderTarget);
	}
}

void OptionsMenu::draw(SDL_Renderer* renderTarget){
	for (std::vector<int>::size_type j = this->menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		this->menuItems->at(j)->draw(renderTarget);
	}
}

void OptionsMenu::toggleSound(SDL_Renderer* renderTarget){
	if (this->soundMuted){
		this->sound->unmute();
		this->soundMuted = false;
		this->menuItems->at(Choices::Sound_On_Off)->setText(renderTarget, "Sound On");
	}
	else{
		this->sound->mute();
		this->soundMuted = true;
		this->menuItems->at(Choices::Sound_On_Off)->setText(renderTarget, "Sound Off");
	}
	center();
}

void OptionsMenu::center(){
	for (std::vector<int>::size_type j = this->menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		int xPosition = (cameraRect->w / 2) - (this->menuItems->at(j)->getWidth() / 2) - cameraRect->x;
		this->menuItems->at(j)->setXPosition(xPosition);

		int previousHeight = 0;
		for (size_t h = 0; h < j; h++)
			previousHeight += this->menuItems->at(h)->getHeight();
		int yPosition = (this->cameraRect->h / 2) - this->cameraRect->y - (this->combinedHeight / 2) + (j * this->margin) + previousHeight;
		this->menuItems->at(j)->setYPosition(yPosition);
	}
}
