#include "CreditsMenu.h"


CreditsMenu::CreditsMenu(SDL_Renderer* renderTarget, SDL_Rect* cameraRect)
{
	this->cameraRect = cameraRect;
	this->sound = Sound::getInstance();
	this->creditsFont = TTF_OpenFont("Fonts/Frontman.ttf", 20);
	this->defaultMargin = 5;
	this->largerMargin = 10;

	this->menuItems = new std::vector<MenuItem*>();

	this->lines = new std::vector<std::pair<MenuItem*, int>*>();
	this->lines->push_back(this->createLine(renderTarget, "CreditsMenu: Erik Brandsma", this->defaultMargin));
	this->lines->push_back(this->createLine(renderTarget, "MainMenu: Erik Brandsma", this->defaultMargin));
	this->lines->push_back(this->createLine(renderTarget, "OptionsMenu: Erik Brandsma", this->defaultMargin));
	this->lines->push_back(this->createLine(renderTarget, "Map: Aaron Kieboom", this->largerMargin));
	this->center();
}


CreditsMenu::~CreditsMenu()
{
	for (size_t c = 0; c < this->lines->size(); c++)
		delete this->lines->at(c);
	delete this->lines;
}

std::pair<MenuItem*, int>* CreditsMenu::createLine(SDL_Renderer* renderTarget, std::string line, int margin){
	MenuItem* menuItem = new MenuItem(renderTarget, this->creditsFont, "Continue");
	return new std::pair<MenuItem*, int>(menuItem, margin);
}

int CreditsMenu::showMenu(SDL_Renderer* renderTarget){
	this->sound->stopSound(Sound_MainMenu_Theme);
	this->sound->playSound(Sound_Credits_Theme);
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

int CreditsMenu::createMenu(SDL_Renderer* renderTarget){
	SDL_Event event;
	while (1)
	{
		this->time = SDL_GetTicks();
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_QUIT:
				return Choices::Exit;
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->mouseX = event.motion.x;
				this->mouseY = event.motion.y;
				for (size_t index = 0; index < this->menuItems->size(); index++)
					if (mouseX >= this->menuItems->at(index)->getXPosition() && mouseX <= this->menuItems->at(index)->getXPosition() + this->menuItems->at(index)->getWidth() &&
						mouseY >= this->menuItems->at(index)->getYPosition() && mouseY <= this->menuItems->at(index)->getYPosition() + this->menuItems->at(index)->getHeight()){
						this->sound->playSound(Sound_MainMenu_Click);
					}

				break;
			}
		}
		SDL_RenderClear(renderTarget);
		this->draw(renderTarget);
		SDL_RenderPresent(renderTarget);
	}
}

void CreditsMenu::draw(SDL_Renderer* renderTarget){
	for (size_t c = 0; c < this->lines->size(); c++){
		this->lines->at(c)->first->draw(renderTarget);
	}
}

void CreditsMenu::center(){
	for (size_t c = 0; c < this->lines->size(); c++){
		MenuItem* item = this->lines->at(c)->first;
		item->setYPosition(-100);
		item->setXPositon(this->cameraRect->w / 2 - item->getWidth() / 2);
	}
}

int CreditsMenu::getBackCode(){
	return Choices::Back;
}

int CreditsMenu::getExitCode(){
	return Choices::Exit;
}

