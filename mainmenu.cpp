#include "mainmenu.h"


MainMenu::MainMenu(SDL_Renderer* renderTarget, SDL_Texture* backgroundImage, SDL_Rect cameraRect, TTF_Font* font)
{
	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = cameraRect.w;
	backgroundImageRect.h = cameraRect.h;
	this->backgroundImage = backgroundImage;

	this->margin = 30;
	this->combinedHeight = 0;

	MenuItem* continueButton	= new MenuItem(renderTarget, font, "Continue");
	MenuItem* exitButton		= new MenuItem(renderTarget, font, "Exit");

	this->menuItems = { continueButton, exitButton };

	for (std::vector<int>::size_type i = this->menuItems.size() - 1; i != (std::vector<int>::size_type) - 1; i--) {
		this->combinedHeight += this->menuItems[i]->getHeight();
		int xPosition = (cameraRect.w / 2) - (this->menuItems[i]->getWidth() / 2) - cameraRect.x;
		this->menuItems[i]->setXPositon(xPosition);
	}

	int marginHeight = ((this->menuItems.size() - 1) * margin);
	combinedHeight += marginHeight;

	for (std::vector<int>::size_type j = this->menuItems.size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		int previousHeight = 0;
		for (int h = 0; h < j; h++)
			previousHeight += this->menuItems[h]->getHeight();
		int yPosition = (cameraRect.h / 2) - cameraRect.y - (combinedHeight / 2) + (j * margin) + previousHeight;
		this->menuItems[j]->setYPosition(yPosition);
	}
}


MainMenu::~MainMenu()
{

}

int MainMenu::showMenu(SDL_Renderer* renderTarget){
	SDL_Event event;
	while (1)
	{
		this->time = SDL_GetTicks();
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_QUIT:
				return 1;
			case SDL_MOUSEMOTION:
				this->mouseX = event.motion.x;
				this->mouseY = event.motion.y;
				for (int i = 0; i < this->menuItems.size(); i++)
					this->menuItems[i]->checkHover(this->mouseX, this->mouseY);
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->mouseX = event.motion.x;
				this->mouseY = event.motion.y;
				for (int index = 0; index < this->menuItems.size(); index++)
					if (mouseX >= this->menuItems[index]->getXPosition() && mouseX <= this->menuItems[index]->getXPosition() + this->menuItems[index]->getWidth() &&
						mouseY >= this->menuItems[index]->getYPosition() && mouseY <= this->menuItems[index]->getYPosition() + this->menuItems[index]->getHeight())
						return index;
				break;
			}
		}
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, this->backgroundImage, &this->backgroundImageRect, NULL);
		this->draw(renderTarget);
		SDL_RenderPresent(renderTarget);
	}
}

void MainMenu::draw(SDL_Renderer* renderTarget){
	for (std::vector<int>::size_type j = this->menuItems.size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		this->menuItems[j]->draw(renderTarget);
	}
}