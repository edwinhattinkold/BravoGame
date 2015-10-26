#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, SDL_Rect* cameraRect, TTF_Font* font)
{
	this->sound = Sound::getInstance();
	this->sound->playSoundLooping(Sound_MainMenu_Theme, 0.50f);

	this->optionsMenu = new OptionsMenu(renderTarget, backgroundImage, cameraRect, font);
	this->creditsMenu = new CreditsMenu(renderTarget, cameraRect);

	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = cameraRect->w;
	backgroundImageRect.h = cameraRect->h;
	this->backgroundImage = backgroundImage;

	this->margin = 40;
	this->combinedHeight = 0;
	
	this->menuItems = new std::vector<MenuItem*>();
	this->menuItems->push_back(new MenuItem(renderTarget, font, "Continue"));
	this->menuItems->push_back(new MenuItem(renderTarget, font, "Load Game"));
	this->menuItems->push_back(new MenuItem(renderTarget, font, "Options"));
	this->menuItems->push_back(new MenuItem(renderTarget, font, "Credits"));
	this->menuItems->push_back(new MenuItem(renderTarget, font, "Exit"));


	for (std::vector<int>::size_type i = this->menuItems->size() - 1; i != (std::vector<int>::size_type) - 1; i--) {
		this->combinedHeight += this->menuItems->at(i)->getHeight();
		int xPosition = (cameraRect->w / 2) - (this->menuItems->at(i)->getWidth() / 2) - cameraRect->x;
		this->menuItems->at(i)->setXPosition(xPosition);
	}

	int marginHeight = ((this->menuItems->size() - 1) * margin);
	combinedHeight += marginHeight;

	for (std::vector<int>::size_type j = this->menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		int previousHeight = 0;
		for (size_t h = 0; h < j; h++)
			previousHeight += this->menuItems->at(h)->getHeight();
		int yPosition = (cameraRect->h / 2) - cameraRect->y - (combinedHeight / 2) + (j * margin) + previousHeight;
		this->menuItems->at(j)->setYPosition(yPosition);
	}
}

MainMenu::~MainMenu()
{
	for (size_t c = 0; c < this->menuItems->size(); c++){
		delete this->menuItems->at(c);				this->menuItems->at(c) = nullptr;
	}
	delete this->menuItems;							this->menuItems = nullptr;
	delete this->optionsMenu;						this->optionsMenu = nullptr;
	delete this->creditsMenu;						this->creditsMenu = nullptr;
}

int MainMenu::getExitCode(){
	return Choices::Exit;
}

int MainMenu::showMenu(SDL_Renderer* renderTarget){
	int choice = this->createMenu(renderTarget);
	switch (choice){
	case(Choices::Continue) :
		this->sound->stopSound(Sound_MainMenu_Theme);
		return Choices::Continue;
		break;
	case(Choices::Load_Game) :
		this->sound->stopSound(Sound_MainMenu_Theme);
		return Choices::Load_Game;
		break;
	case(Choices::Options) :
		this->optionsChoice = this->optionsMenu->showMenu(renderTarget);
		if (this->optionsChoice == this->optionsMenu->getBackCode())
			return this->showMenu(renderTarget);
		else if (this->optionsChoice == this->optionsMenu->getExitCode())
			return Choices::Exit;
		break;
	case(Choices::Credits) :
		this->sound->fadeOut();
		this->creditsChoice = this->creditsMenu->showMenu(renderTarget);
		if (this->creditsChoice == this->creditsMenu->getBackCode())
			return this->showMenu(renderTarget);
		else if (this->creditsChoice == this->creditsMenu->getExitCode())
			return Choices::Exit;
		break;
	case(Choices::Exit):
		return Choices::Exit;
		break;
	default:
		return Choices::Exit;
		break;
	}
}

int MainMenu::createMenu(SDL_Renderer* renderTarget){
	SDL_Event event;
	while (1)
	{
		if (this->sound->getVolume() != 1.00f)
			this->sound->fadeInTick();

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

void MainMenu::draw(SDL_Renderer* renderTarget){
	for (size_t c = 0; c < this->menuItems->size(); c++) {
		this->menuItems->at(c)->draw(renderTarget);
	}
}