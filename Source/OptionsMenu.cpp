#include "OptionsMenu.h"
#include "CustomCursor.h"

OptionsMenu::OptionsMenu(SDL_Renderer* renderTarget, SDL_Window* window, SDL_Texture* backgroundImage, Sprite* arrow, Camera* camera, TTF_Font* font)
{
	this->arrow = arrow;
	this->renderTarget = renderTarget;
	this->window = window;
	settings = Settings::getInstance();
	this->camera = camera;
	sound = Sound::getInstance();
	backgroundImageRect.x = 0;
	backgroundImageRect.y = 0;
	backgroundImageRect.w = camera->getCamera()->w;
	backgroundImageRect.h = camera->getCamera()->h;
	this->backgroundImage = backgroundImage;

	margin = 40;
	combinedHeight = 0;

	menuItems = new std::vector<MenuItem*>();
	menuItems->push_back( new MenuItem( renderTarget, font, "Fullscreen on" ) );
	menuItems->push_back(new MenuItem(renderTarget, font, "Sound on"));
	menuItems->push_back(new MenuItem(renderTarget, font, "Back"));

	for (std::vector<int>::size_type i = menuItems->size() - 1; i != (std::vector<int>::size_type) - 1; i--) {
		combinedHeight += menuItems->at(i)->getHeight();
		int xPosition = (camera->getCamera()->w / 2) - (menuItems->at(i)->getWidth() / 2) - camera->getCamera()->x;
		menuItems->at(i)->setXPosition(xPosition);
	}

	int marginHeight = ((menuItems->size() - 1) * margin);
	combinedHeight += marginHeight;

	selected = 0;
	
	soundOn = settings->getBoolean( Settings_SoundOn );
	fullscreen = settings->getBoolean( Settings_fullscreen );
	updateSound( renderTarget );
	updateFullscreen( renderTarget );
}

OptionsMenu::~OptionsMenu()
{
	for (size_t c = 0; c < menuItems->size(); c++)
		delete menuItems->at(c);
	delete menuItems;
}

int OptionsMenu::getBackCode(){
	return Choices::Back;
}

int OptionsMenu::getExitCode(){
	return Choices::Exit;
}

int OptionsMenu::showMenu(SDL_Renderer* renderTarget){
	SDL_GetMouseState( &mouseX, &mouseY );
	CustomCursor::getInstance( )->draw( mouseX, mouseY );
	center();
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

int OptionsMenu::createMenu(SDL_Renderer* renderTarget){
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
					if( i != selected && menuItems->at( i )->checkHover( mouseX, mouseY ) )
					{
						sound->playSound( Sound_MainMenu_Tick );
						selected = i;
						updateSelected();
					}
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseX = ev.motion.x;
				mouseY = ev.motion.y;
				for (size_t index = 0; index < menuItems->size(); index++)
					if (mouseX >= menuItems->at(index)->getXPosition() && mouseX <= menuItems->at(index)->getXPosition() + menuItems->at(index)->getWidth() &&
						mouseY >= menuItems->at(index)->getYPosition() && mouseY <= menuItems->at(index)->getYPosition() + menuItems->at(index)->getHeight()){
						sound->playSound(Sound_MainMenu_Click);
						
						if( index == Choices::Back )
							return index;
						else
							handleSelection( index );
					}
				break;
			case SDL_KEYDOWN:
				SDL_Keycode keyPressed = ev.key.keysym.sym;
				handleKeyboardInput( keyPressed );
				if( keyPressed == SDLK_RETURN || keyPressed == SDLK_SPACE)
				{
					sound->playSound( Sound_MainMenu_Click );
					if( selected == Choices::Back )
						return selected;
					else
						handleSelection( selected );
				}
				else if( keyPressed == SDLK_ESCAPE )
					return Choices::Back;
				break;
			}
		}
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, backgroundImage, NULL, NULL);
		drawMenuItems(renderTarget);
		arrow->draw( renderTarget );
		CustomCursor::getInstance( )->draw( mouseX, mouseY );
		SDL_RenderPresent(renderTarget);
	}
}

void OptionsMenu::drawMenuItems( SDL_Renderer* renderTarget )
{
	for (std::vector<int>::size_type j = menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		menuItems->at(j)->draw(renderTarget);
	}
}

void OptionsMenu::toggleSound(SDL_Renderer* renderTarget){
	if (soundOn){
		sound->mute();
		soundOn = false;
		menuItems->at( Choices::Sound_On_Off )->setText( renderTarget, "Sound Off" );
	}
	else{
		sound->unmute();
		soundOn = true;
		menuItems->at( Choices::Sound_On_Off )->setText( renderTarget, "Sound On" );
	}
	menuItems->at( Choices::Sound_On_Off )->setHighlighted();
	settings->setBoolean( Settings_SoundOn, soundOn );
	center();
}

void OptionsMenu::updateSound(SDL_Renderer* renderTarget)
{
	if( soundOn )
	{
		sound->unmute();
		menuItems->at( Choices::Sound_On_Off )->setText( renderTarget, "Sound On" );
	}
	else
	{
		sound->mute();
		menuItems->at( Choices::Sound_On_Off )->setText( renderTarget, "Sound Off" );
	}
	center();
}

void OptionsMenu::toggleFullscreen( SDL_Renderer* renderTarget )
{
	Uint32 flags;
	int windowWidth = 0;
	int windowHeight = 0;

	if( fullscreen )
	{
		flags = 0;
		windowWidth = 1280;
		windowHeight = 720;
		fullscreen = false;
		menuItems->at( Choices::FullScreen_On_Off )->setText( renderTarget, "Fullscreen off" );
	}
	else
	{
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
		getDesktopResolution( windowWidth, windowHeight );
		fullscreen = true;
		menuItems->at( Choices::FullScreen_On_Off )->setText( renderTarget, "Fullscreen on" );
	}
	SDL_SetWindowSize( window, windowWidth, windowHeight );
	SDL_SetWindowFullscreen( window, flags );
	camera->getCamera()->w = windowWidth;
	camera->getCamera()->h = windowHeight;
	camera->windowWidth = windowWidth;
	camera->windowHeight = windowHeight;
	menuItems->at( Choices::FullScreen_On_Off )->setHighlighted();
	settings->setBoolean( Settings_fullscreen, fullscreen );
	center();
}

void OptionsMenu::updateFullscreen( SDL_Renderer* renderTarget )
{
	if( fullscreen )
		menuItems->at( Choices::FullScreen_On_Off )->setText( renderTarget, "Fullscreen On" );
	else
		menuItems->at( Choices::FullScreen_On_Off )->setText( renderTarget, "Fullscreen Off" );
	center();
}

void OptionsMenu::center(){
	for (std::vector<int>::size_type j = menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j--) {
		int xPosition = (camera->getCamera()->w / 2) - (menuItems->at( j )->getWidth() / 2);
		menuItems->at(j)->setXPosition(xPosition);

		int previousHeight = 0;
		for (size_t h = 0; h < j; h++)
			previousHeight += menuItems->at(h)->getHeight();
		int yPosition = (camera->getCamera()->h / 2) - (combinedHeight / 2) + (j * margin) + previousHeight;
		menuItems->at(j)->setYPosition(yPosition);
	}
	updateSelected();
}

void OptionsMenu::getDesktopResolution( int& horizontal, int& vertical )
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect( hDesktop, &desktop );
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void OptionsMenu::handleKeyboardInput( SDL_Keycode keyPressed )
{
	switch( keyPressed )
	{
		case(SDLK_w) :
		case(SDLK_UP) :
			if( selected != 0 )
				selected--;
			else
				selected = menuItems->size() - 1;
			sound->playSound( Sound_MainMenu_Tick );
			break;
		case(SDLK_s) :
		case(SDLK_DOWN) :
			if( selected != menuItems->size() - 1 )
				selected++;
			else
				selected = 0;
			sound->playSound( Sound_MainMenu_Tick );
			break;
	}
	updateSelected();
}

void OptionsMenu::updateSelected()
{
	MenuItem* selectedItem = menuItems->at( selected );
	for( size_t c = 0; c < menuItems->size(); c++ )
		menuItems->at( c )->setColor( renderTarget, Red );
	menuItems->at( selected )->setColor( renderTarget, SelectedRed );
	arrow->positionRect.x = selectedItem->getXPosition() - arrow->positionRect.w - 20;
	arrow->positionRect.y = selectedItem->getYPosition() + selectedItem->getHeight() / 2 - arrow->positionRect.h / 2 - 3;
}

void OptionsMenu::handleSelection(int index)
{
	if( index == Choices::Sound_On_Off )
		toggleSound( renderTarget );
	else if( index == Choices::FullScreen_On_Off )
		toggleFullscreen( renderTarget );
}