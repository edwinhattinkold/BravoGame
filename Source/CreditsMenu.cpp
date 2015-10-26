#include "CreditsMenu.h"
#include <math.h> 

CreditsMenu::CreditsMenu(SDL_Renderer* renderTarget, SDL_Rect* cameraRect)
{ 
	this->cameraRect = cameraRect;
	this->sound = Sound::getInstance();
	this->creditsTitelFont = TTF_OpenFont("Fonts/frontman.ttf", 50);
	this->creditsDefaultFont = TTF_OpenFont("Fonts/atrox.ttf", 50);
	this->creditsMainTitelFont = TTF_OpenFont("Fonts/atrox.ttf", cameraRect->w / 10);
	this->defaultMargin = 1;
	this->largerMargin = 35;
	this->titelSpacing = 10;
	this->speed = this->cameraRect->h / 9;

	this->menuItems = new std::vector<MenuItem*>();

	MenuItem* backButton = new MenuItem(renderTarget, this->creditsTitelFont, "Back");
	backButton->setXPosition(20);
	backButton->setYPosition(cameraRect->h - backButton->getHeight() - 10);
	this->menuItems->push_back(backButton);

	this->lines = new std::vector<std::pair<MenuItem*, int>*>();
	this->lines->push_back(this->createLine(renderTarget, "TerrorEdje!",				LineType::MainTitel,	0));

	this->lines->push_back(this->createLine(renderTarget, "Developers",					LineType::Titel,		cameraRect->h / 2));
	this->lines->push_back(this->createLine(renderTarget, "Sven van den Boogaard",		LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "Ivan Horn",					LineType::Default,		this->defaultMargin));
	this->lines->push_back(this->createLine(renderTarget, "Edwin Hattink",				LineType::Default,		this->defaultMargin));
	this->lines->push_back(this->createLine(renderTarget, "Aaron Kieboom",				LineType::Default,		this->defaultMargin));
	this->lines->push_back(this->createLine(renderTarget, "Erik Brandsma",				LineType::Default,		this->defaultMargin));

	this->lines->push_back(this->createLine(renderTarget, "Physics",					LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Sven van den Boogaard",		LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "Ivan horn",					LineType::Default,		this->defaultMargin));

	this->lines->push_back(this->createLine(renderTarget, "Map",						LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Aaron Kieboom",				LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "Edwin Hattink",				LineType::Default,		this->defaultMargin));

	this->lines->push_back(this->createLine(renderTarget, "Menus",						LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Erik Brandsma",				LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Sound",						LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Erik Brandsma",				LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Git Master",					LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Edwin Hattink",				LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Test Manager",				LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Ivan Horn",					LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Scrum master",				LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Erik Brandsma",				LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Product owner",				LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Edwin Hattink",				LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Boss",						LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Bob van der Putten",			LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Customer",					LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Bob van der putten",			LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Special thanks",				LineType::Titel,		this->largerMargin));
	this->lines->push_back(this->createLine(renderTarget, "Wokmeneer",					LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "Die ene dönerzaak",			LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "OB205",						LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "Google",						LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "Stackoverflow",				LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "iForce2d tutorials",			LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "CodingMadeEasy tutorials",	LineType::Default,		this->titelSpacing));
	this->lines->push_back(this->createLine(renderTarget, "Thecplusplusguy tutorials",	LineType::Default,		this->titelSpacing));

	this->lines->push_back(this->createLine(renderTarget, "Thanks for playing!",		LineType::MainTitel,	this->cameraRect->h / 2));
}

CreditsMenu::~CreditsMenu()
{
	for (size_t c = 0; c < this->lines->size(); c++){
		delete this->lines->at(c)->first;		this->lines->at(c)->first = nullptr;
		delete this->lines->at(c);				this->lines->at(c) = nullptr;
	}
	delete this->lines;

	for (size_t x = 0; x < this->menuItems->size(); x++){
		delete this->menuItems->at(x);			this->menuItems->at(x) = nullptr;
	}
	delete this->menuItems;						this->menuItems = nullptr;

	TTF_CloseFont(this->creditsDefaultFont);	this->creditsDefaultFont = nullptr;
	TTF_CloseFont(this->creditsMainTitelFont);	this->creditsMainTitelFont = nullptr;
	TTF_CloseFont(this->creditsTitelFont);		this->creditsTitelFont = nullptr;
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
	case(LineType::MainTitel) :
		fontToUse = this->creditsMainTitelFont;
		colorToUse = Color::White;
	}

	MenuItem* menuItem = new MenuItem(renderTarget, fontToUse, line);
	menuItem->setColor(renderTarget, colorToUse);
	return new std::pair<MenuItem*, int>(menuItem, margin);
}

int CreditsMenu::showMenu(SDL_Renderer* renderTarget){
	this->previousTime = SDL_GetTicks();;
	this->currentTime = SDL_GetTicks();;
	this->deltaTime = 0.0f;
	this->pastTime = 0.0f;
	this->positionAllLines();

	this->sound->stopSound(Sound_MainMenu_Theme);
	this->sound->playSound(Sound_Credits_Theme);

	SDL_Delay(200);

	int choice = this->createMenu(renderTarget);
	switch (choice){
	case(Choices::Back) :
		this->sound->fadeOut();
		this->sound->stopSound(Sound_Credits_Theme);
		this->sound->playSound(Sound_MainMenu_Theme, 0.5f);
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
	bool needsToFadeIn = true;
	while (1)
	{
		if (this->sound->getVolume() != 1.00f && needsToFadeIn)
			this->sound->fadeInTick();
		else
			needsToFadeIn = false;

		this->previousTime = this->currentTime;
		this->currentTime = SDL_GetTicks();
		this->deltaTime = (this->currentTime - this->previousTime) / 1000.0f;
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_QUIT:
				return Choices::Exit;
				break;
			case SDL_MOUSEMOTION:
				this->mouseX = event.motion.x;
				this->mouseY = event.motion.y;
				for (size_t i = 0; i < this->menuItems->size(); i++)
					this->menuItems->at(i)->checkHover(this->mouseX, this->mouseY);
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
		if (this->isDone())
			return Choices::Back;

		SDL_RenderClear(renderTarget);
		this->update(deltaTime);
		this->draw(renderTarget);
		SDL_RenderPresent(renderTarget);
		SDL_Delay(1000 / 60);
	}
}

void CreditsMenu::update(float deltaTime){
	if (shouldMove(deltaTime)){
		float fps = (1 / deltaTime);
		int pixels = int(round(this->speed / fps));
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
	if (this->lines->at(this->lines->size() - 1)->first->getYPosition() < -100){
		if (this->sound->getVolume() != 0.00f){
			this->sound->fadeOutTick();
		}
		else
			return true;
	}
	return false;

}

void CreditsMenu::draw(SDL_Renderer* renderTarget){
	for (size_t c = 0; c < this->lines->size(); c++)
		this->lines->at(c)->first->draw(renderTarget);
	for (size_t x = 0; x < this->menuItems->size(); x++)
		this->menuItems->at(x)->draw(renderTarget);
}

void CreditsMenu::positionAllLines(){
	for (size_t c = 0; c < this->lines->size(); c++){
		MenuItem* item = this->lines->at(c)->first;
		int previousDistance = 0;
		for (size_t x = 0; x <= c; x++)
			previousDistance += (this->lines->at(x)->first->getHeight() + this->lines->at(x)->second);

		if (c == 0)
			previousDistance = 0;

		item->setYPosition(this->cameraRect->h / 2 - item->getHeight() / 2 + previousDistance);
		item->setXPosition(this->cameraRect->w / 2 - item->getWidth() / 2);
	}
}

int CreditsMenu::getBackCode(){
	return Choices::Back;
}

int CreditsMenu::getExitCode(){
	return Choices::Exit;
}