#include "HowToPlay.h"
HowToPlay::HowToPlay(SDL_Renderer* renderTarget, Camera* camera, TTF_Font* font){
	this->camera = camera;
	sound = Sound::getInstance();
	//sound->playSoundLooping(Sound_MainMenu_Theme, 0.50f);
	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = camera->getCamera()->w;
	backgroundImageRect.h = camera->getCamera()->h;
	backgroundImage = new Sprite(renderTarget, Asset_HowTo, 0, 0, 1, 1, 0);
	menuItems = new std::vector<MenuItem*>();

	backButton = new MenuItem(renderTarget, font, "Back");
	menuItems->push_back(backButton);
	backButton->setXPosition(20);
	backButton->setColor(renderTarget, SelectedRed);
}

HowToPlay::~HowToPlay(){
	for (size_t i = 0; i < menuItems->size(); i++){
		delete menuItems->at(i);	menuItems->at(i) = nullptr;
	}
	delete menuItems;				menuItems = nullptr;
	delete backgroundImage;			backgroundImage = nullptr;
}


int HowToPlay::showMenu(SDL_Renderer* renderTarget){
	SDL_GetMouseState(&mouseX, &mouseY);
	CustomCursor::getInstance()->draw(mouseX, mouseY);
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

int HowToPlay::createMenu(SDL_Renderer* renderTarget){
	while (1)
	{
		time = SDL_GetTicks();
		while (SDL_PollEvent(&ev)){
			switch (ev.type){
			case SDL_QUIT:
				return Choices::Exit;
			case SDL_MOUSEMOTION:
				mouseX = ev.motion.x;
				mouseY = ev.motion.y;
				for (size_t i = 0; i < menuItems->size(); i++)
				if (menuItems->at(i)->checkHover(mouseX, mouseY))
					sound->playSound(Sound_MainMenu_Tick);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseX = ev.motion.x;
				mouseY = ev.motion.y;
				for (size_t index = 0; index < menuItems->size(); index++)
				if (mouseX >= menuItems->at(index)->getXPosition() && mouseX <= menuItems->at(index)->getXPosition() + menuItems->at(index)->getWidth() &&
					mouseY >= menuItems->at(index)->getYPosition() && mouseY <= menuItems->at(index)->getYPosition() + menuItems->at(index)->getHeight()){
					sound->playSound(Sound_MainMenu_Click);
					return index;
				}
				break;
			case SDL_KEYDOWN:
				SDL_Keycode keyPressed = ev.key.keysym.sym;
				if (keyPressed == SDLK_RETURN || keyPressed == SDLK_SPACE || keyPressed == SDLK_ESCAPE){
					sound->playSound(Sound_MainMenu_Click);
					return Choices::Back;
				}
				break;
			}
		}
		SDL_RenderClear(renderTarget);
		backgroundImage->positionRect = *camera->getCamera();
		backgroundImage->positionRect.x = 0;
		backgroundImage->positionRect.y = 0;
		backgroundImage->draw(renderTarget);
		backButton->setYPosition(camera->getCamera()->h - backButton->getHeight() - 10);
		draw(renderTarget);
		CustomCursor::getInstance()->draw(mouseX, mouseY);
		SDL_RenderPresent(renderTarget);
	}
}

void HowToPlay::draw(SDL_Renderer* renderTarget)
{
	
	for (size_t x = 0; x < menuItems->size(); x++)
		menuItems->at(x)->draw(renderTarget);
}
int HowToPlay::getBackCode(){
	return Back;
}