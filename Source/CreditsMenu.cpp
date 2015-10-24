#include "CreditsMenu.h"
#include <math.h> 

CreditsMenu::CreditsMenu(SDL_Renderer* renderTarget, SDL_Rect* cameraRect)
{ 
	this->cameraRect = cameraRect;
	this->sound = Sound::getInstance();
	TTF_Font* creditsDefaultFont;
	this->creditsTitelFont = TTF_OpenFont("Fonts/frontman.ttf", 50);
	this->creditsDefaultFont = TTF_OpenFont("Fonts/atrox.ttf", 50);
	this->defaultMargin = 1;
	this->largerMargin = 35;
	this->titelSpacing = 10;
	this->speed = 50;

	this->menuItems = new std::vector<MenuItem*>();

	this->lines = new std::vector<std::pair<MenuItem*, int>*>();
	this->lines->push_back(this->createLine(renderTarget, "TerrorEdje",				LineType::MainTitel,	0));

	this->lines->push_back(this->createLine(renderTarget, "Developers",				LineType::Titel,		cameraRect->h / 2));
	this->lines->push_back(this->createLine(renderTarget, "Sven van den Boogaard",	LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "Ivan Horn",				LineType::Default,		this->defaultMargin));
	this->lines->push_back(this->createLine(renderTarget, "Edwin Hattink",			LineType::Default,		this->defaultMargin));
	this->lines->push_back(this->createLine(renderTarget, "Aaron Kieboom",			LineType::Default,		this->defaultMargin));
	this->lines->push_back(this->createLine(renderTarget, "Erik Brandsma",			LineType::Default,		this->defaultMargin));

	this->lines->push_back(this->createLine(renderTarget, "Physics",				LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Sven van den Boogaard",	LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "Ivan horn",				LineType::Default,		this->defaultMargin));

	this->lines->push_back(this->createLine(renderTarget, "Menus",					LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Erik Brandsma",			LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Map",					LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Aaron Kieboom",			LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "Edwin Hattink",			LineType::Default,		this->defaultMargin));

	this->lines->push_back(this->createLine(renderTarget, "Sound",					LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Erik Brandsma",			LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Git Master",				LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Edwin Hattink",			LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Test Manager",			LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Ivan Horn",				LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Scrum master",			LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Erik Brandsma",			LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Product owner",			LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Edwin Hattink",			LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Boss",					LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Bob van der Putten",		LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Customer",				LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Bob van der putten",		LineType::Default,		this->titelSpacing));
}


CreditsMenu::~CreditsMenu()
{
	for (size_t c = 0; c < this->lines->size(); c++)
		delete this->lines->at(c);
	delete this->lines;
}

std::pair<MenuItem*, int>* CreditsMenu::createLine(SDL_Renderer* renderTarget, char * line, LineType lineType, int margin){
	TTF_Font* fontToUse;
	Color colorToUse;

	switch (lineType){
	case(LineType::Titel) :
		fontToUse = this->creditsTitelFont;
		colorToUse = Color::Red;
		break;
	case(LineType::Default) :
		fontToUse = this->creditsDefaultFont;
		colorToUse = Color::White;
		break;
	case(LineType::MainTitel):
		fontToUse = TTF_OpenFont("Fonts/frontman.ttf", 80);
		colorToUse = Color::White;
	}

	MenuItem* menuItem = new MenuItem(renderTarget, fontToUse, line);
	menuItem->setColor(renderTarget, colorToUse);
	return new std::pair<MenuItem*, int>(menuItem, margin);
}

int CreditsMenu::showMenu(SDL_Renderer* renderTarget){
	this->previousTime = 0;
	this->currentTime = 0;
	this->deltaTime = 0.0f;
	this->pastTime = 0.0f;
	this->positionAllLines();
	this->sound->stopSound(Sound_MainMenu_Theme);
	this->sound->playSound(Sound_Credits_Theme, 0.5f);

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
		this->previousTime = this->currentTime;
		this->currentTime = SDL_GetTicks();
		this->deltaTime = (this->currentTime - this->previousTime) / 1000.0f;
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
		if (this->isDone()){
			this->sound->stopSound(Sound_Credits_Theme);
			this->sound->playSound(Sound_MainMenu_Theme, 0.5f);
			return Choices::Back;
		}

		SDL_RenderClear(renderTarget);
		this->update(deltaTime);
		this->draw(renderTarget);
		SDL_RenderPresent(renderTarget);
	}
}

void CreditsMenu::update(float deltaTime){
	if (shouldMove(deltaTime)){
		float fps = (1 / deltaTime);
		int pixels = round(this->speed / fps);
		for (size_t c = 0; c < this->lines->size(); c++)
			this->lines->at(c)->first->setYPosition(this->lines->at(c)->first->getYPosition() - pixels);
	}
}

bool CreditsMenu::shouldMove(float deltaTime){
	if (this->pastTime > 2.5f)
		return true;
	else
		this->pastTime += deltaTime;
	return false;
}

bool CreditsMenu::isDone(){
	return (this->lines->at(this->lines->size() - 1)->first->getYPosition() < -100);
}

void CreditsMenu::draw(SDL_Renderer* renderTarget){
	for (size_t c = 0; c < this->lines->size(); c++)
		this->lines->at(c)->first->draw(renderTarget);
}

void CreditsMenu::positionAllLines(){
	for (size_t c = 0; c < this->lines->size(); c++){
		MenuItem* item = this->lines->at(c)->first;
		int previousDistance = 0;
		for (int x = 0; x <= c; x++)
			previousDistance += (this->lines->at(x)->first->getHeight() + this->lines->at(x)->second);

		if (c == 0)
			previousDistance = 0;

		item->setYPosition(this->cameraRect->h / 2 - item->getHeight() / 2 + previousDistance);
		item->setXPositon(this->cameraRect->w / 2 - item->getWidth() / 2);
	}
}

int CreditsMenu::getBackCode(){
	return Choices::Back;
}

int CreditsMenu::getExitCode(){
	return Choices::Exit;
}