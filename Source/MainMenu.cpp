#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, SDL_Rect* cameraRect, TTF_Font* font)
{
	sound = Sound::getInstance();
	sound->playSoundLooping(Sound_MainMenu_Theme, 0.50f);

	optionsMenu = new OptionsMenu(renderTarget, backgroundImage, cameraRect, font);
	creditsMenu = new CreditsMenu(renderTarget, cameraRect);

	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = cameraRect->w;
	backgroundImageRect.h = cameraRect->h;
	this->backgroundImage = backgroundImage;

	margin = 40;
	combinedHeight = 0;
	
	menuItems = new std::vector<MenuItem*>();
	menuItems->push_back(new MenuItem(renderTarget, font, "Continue"));
	menuItems->push_back(new MenuItem(renderTarget, font, "Load Game"));
	menuItems->push_back(new MenuItem(renderTarget, font, "Options"));
	menuItems->push_back(new MenuItem(renderTarget, font, "Credits"));
	menuItems->push_back(new MenuItem(renderTarget, font, "Exit"));


	for (std::vector<int>::size_type i = menuItems->size() - 1; i != (std::vector<int>::size_type) - 1; i--) {
		combinedHeight += menuItems->at(i)->getHeight();
		int xPosition = (cameraRect->w / 2) - (menuItems->at(i)->getWidth() / 2) - cameraRect->x;
		menuItems->at(i)->setXPosition(xPosition);
	}

	int marginHeight = ((menuItems->size() - 1) * margin);
	combinedHeight += marginHeight;

	for (std::vector<int>::size_type j = menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		int previousHeight = 0;
		for (size_t h = 0; h < j; h++)
			previousHeight += menuItems->at(h)->getHeight();
		int yPosition = (cameraRect->h / 2) - cameraRect->y - (combinedHeight / 2) + (j * margin) + previousHeight;
		menuItems->at(j)->setYPosition(yPosition);
	}
}

MainMenu::~MainMenu()
{
	for (size_t c = 0; c < menuItems->size(); c++){
		delete menuItems->at(c);			menuItems->at(c) = nullptr;
	}
	delete menuItems;						menuItems = nullptr;
	delete optionsMenu;						optionsMenu = nullptr;
	delete creditsMenu;						creditsMenu = nullptr;
}

int MainMenu::getExitCode(){
	return Choices::Exit;
}

int MainMenu::showMenu(SDL_Renderer* renderTarget){
	int choice = createMenu(renderTarget);
	switch (choice){
	case(Choices::Continue) :
		sound->stopSound(Sound_MainMenu_Theme);
		return Choices::Continue;
		break;
	case(Choices::Load_Game) :
		sound->stopSound(Sound_MainMenu_Theme);
		return Choices::Load_Game;
		break;
	case(Choices::Options) :
		optionsChoice = optionsMenu->showMenu(renderTarget);
		if (optionsChoice == optionsMenu->getBackCode())
			return showMenu(renderTarget);
		else
			return Choices::Exit;
		break;
	case(Choices::Credits) :
		sound->fadeOut();
		creditsChoice = creditsMenu->showMenu(renderTarget);
		if (creditsChoice == creditsMenu->getBackCode())
			return showMenu(renderTarget);
		else
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
		if (sound->getVolume() != 1.00f)
			sound->fadeInTick();

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

void MainMenu::draw(SDL_Renderer* renderTarget){
	for (size_t c = 0; c < menuItems->size(); c++) {
		menuItems->at(c)->draw(renderTarget);
	}
}