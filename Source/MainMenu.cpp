#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, SDL_Rect cameraRect, TTF_Font* font)
{
	this->sound = Sound::getInstance();
	this->sound->playSoundLooping("rock_intro.mp3", 0.50f);
	this->optionsMenu = new OptionsMenu(renderTarget, backgroundImage, cameraRect, font);
	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = cameraRect.w;
	backgroundImageRect.h = cameraRect.h;
	this->backgroundImage = backgroundImage;

	this->margin = 40;
	this->combinedHeight = 0;

	this->menuItems = { new MenuItem(renderTarget, font, "Continue"),
						new MenuItem(renderTarget, font, "Load game"),
						new MenuItem(renderTarget, font, "Options"),
						new MenuItem(renderTarget, font, "Exit")
					};

	for (std::vector<int>::size_type i = this->menuItems.size() - 1; i != (std::vector<int>::size_type) - 1; i--) {
		this->combinedHeight += this->menuItems[i]->getHeight();
		int xPosition = (cameraRect.w / 2) - (this->menuItems[i]->getWidth() / 2) - cameraRect.x;
		this->menuItems[i]->setXPositon(xPosition);
	}

	int marginHeight = ((this->menuItems.size() - 1) * margin);
	combinedHeight += marginHeight;

	for (std::vector<int>::size_type j = this->menuItems.size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		int previousHeight = 0;
		for (size_t h = 0; h < j; h++)
			previousHeight += this->menuItems[h]->getHeight();
		int yPosition = (cameraRect.h / 2) - cameraRect.y - (combinedHeight / 2) + (j * margin) + previousHeight;
		this->menuItems[j]->setYPosition(yPosition);
	}
}

MainMenu::~MainMenu()
{
	for (size_t c = 0; c < this->menuItems.size(); c++)
		delete this->menuItems[c];
	delete this->optionsMenu;
}

int MainMenu::getExitCode(){
	return Choices::Exit;
}

int MainMenu::showMenu(SDL_Renderer* renderTarget){
	int choice = this->createMenu(renderTarget);
	switch (choice){
	case(Choices::Continue) :
			this->sound->stopSound("rock_intro.mp3");
			break;
		case(Choices::Load_Game) :
			this->sound->stopSound("rock_intro.mp3");
			break;
		case(Choices::Options) :
			this->optionsChoice = this->optionsMenu->showMenu(renderTarget);
			if (this->optionsChoice == this->optionsMenu->getBackCode())
				this->showMenu(renderTarget);
			else if (this->optionsChoice == this->optionsMenu->getExitCode())
				return Choices::Exit;
			break;
		case(Choices::Exit) :
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
	for (std::vector<int>::size_type j = this->menuItems.size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		this->menuItems[j]->draw(renderTarget);
	}
}