#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, SDL_Rect cameraRect, TTF_Font* font)
{
	this->cameraRect = cameraRect;
	this->sound = Sound::getInstance();
	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = cameraRect.w;
	backgroundImageRect.h = cameraRect.h;
	this->backgroundImage = backgroundImage;

	this->margin = 40;
	this->combinedHeight = 0;

	this->menuItems = { new MenuItem(renderTarget, font, "Sound on"),
						new MenuItem(renderTarget, font, "Back")
	};

	for (std::vector<int>::size_type i = this->menuItems.size() - 1; i != (std::vector<int>::size_type) - 1; i--) {
		this->combinedHeight += this->menuItems[i]->getHeight();
		int xPosition = (cameraRect.w / 2) - (this->menuItems[i]->getWidth() / 2) - cameraRect.x;
		this->menuItems[i]->setXPositon(xPosition);
	}

	int marginHeight = ((this->menuItems.size() - 1) * margin);
	combinedHeight += marginHeight;

	this->center();
	this->soundMuted = false;
}

OptionsMenu::~OptionsMenu()
{
	for (size_t c = 0; c < this->menuItems.size(); c++)
		delete this->menuItems[c];
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
				for (size_t i = 0; i < this->menuItems.size(); i++)
					if (this->menuItems[i]->checkHover(this->mouseX, this->mouseY))
						this->sound->playSound("menu_tick.wav");
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->mouseX = event.motion.x;
				this->mouseY = event.motion.y;
				for (size_t index = 0; index < this->menuItems.size(); index++)
					if (mouseX >= this->menuItems[index]->getXPosition() && mouseX <= this->menuItems[index]->getXPosition() + this->menuItems[index]->getWidth() &&
						mouseY >= this->menuItems[index]->getYPosition() && mouseY <= this->menuItems[index]->getYPosition() + this->menuItems[index]->getHeight()){
						this->sound->playSound("menu_confirm.wav");
						
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
	for (std::vector<int>::size_type j = this->menuItems.size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		this->menuItems[j]->draw(renderTarget);
	}
}

void OptionsMenu::toggleSound(SDL_Renderer* renderTarget){
	if (this->soundMuted){
		this->sound->unmute();
		this->soundMuted = false;
		this->menuItems[Choices::Sound_On_Off]->setText(renderTarget, "Sound On");
	}
	else{
		this->sound->mute();
		this->soundMuted = true;
		this->menuItems[Choices::Sound_On_Off]->setText(renderTarget, "Sound Off");
	}
	center();
}

void OptionsMenu::center(){
	for (std::vector<int>::size_type j = this->menuItems.size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		int xPosition = (cameraRect.w / 2) - (this->menuItems[j]->getWidth() / 2) - cameraRect.x;
		this->menuItems[j]->setXPositon(xPosition);

		int previousHeight = 0;
		for (size_t h = 0; h < j; h++)
			previousHeight += this->menuItems[h]->getHeight();
		int yPosition = (this->cameraRect.h / 2) - this->cameraRect.y - (this->combinedHeight / 2) + (j * this->margin) + previousHeight;
		this->menuItems[j]->setYPosition(yPosition);
	}
}
