#include "CreditsMenu.h"
#include <math.h> 

CreditsMenu::CreditsMenu( SDL_Renderer* renderTarget, SDL_Rect* cameraRect )
{
	this->cameraRect = cameraRect;
	sound = Sound::getInstance();
	creditsTitelFont = TTF_OpenFont( "Fonts/frontman.ttf", 50 );
	creditsDefaultFont = TTF_OpenFont( "Fonts/atrox.ttf", 50 );
	creditsMainTitelFont = TTF_OpenFont( "Fonts/atrox.ttf", cameraRect->w / 10 );
	defaultMargin = 1;
	largerMargin = 35;
	titelSpacing = 10;
	speed = cameraRect->h / 9;

	menuItems = new std::vector<MenuItem*>();

	MenuItem* backButton = new MenuItem( renderTarget, creditsTitelFont, "Back" );
	backButton->setXPosition( 20 );
	backButton->setYPosition( cameraRect->h - backButton->getHeight() - 10 );
	menuItems->push_back( backButton );

	lines = new std::vector<std::pair<MenuItem*, int>*>();
	lines->push_back( createLine( renderTarget, "TerrorEdje!", LineType::MainTitel, 0 ) );

	lines->push_back( createLine( renderTarget, "Developers", LineType::Titel, cameraRect->h / 2 ) );
	lines->push_back( createLine( renderTarget, "Sven van den Boogaard", LineType::Default, titelSpacing ) );
	lines->push_back( createLine( renderTarget, "Ivan Horn", LineType::Default, defaultMargin ) );
	lines->push_back( createLine( renderTarget, "Edwin Hattink", LineType::Default, defaultMargin ) );
	lines->push_back( createLine( renderTarget, "Aaron Kieboom", LineType::Default, defaultMargin ) );
	lines->push_back( createLine( renderTarget, "Erik Brandsma", LineType::Default, defaultMargin ) );

	lines->push_back( createLine( renderTarget, "Physics", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Sven van den Boogaard", LineType::Default, titelSpacing ) );
	lines->push_back( createLine( renderTarget, "Ivan horn", LineType::Default, defaultMargin ) );

	lines->push_back( createLine( renderTarget, "Map", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Aaron Kieboom", LineType::Default, titelSpacing ) );
	lines->push_back( createLine( renderTarget, "Edwin Hattink", LineType::Default, defaultMargin ) );

	lines->push_back( createLine( renderTarget, "Menus", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Erik Brandsma", LineType::Default, titelSpacing ) );

	lines->push_back( createLine( renderTarget, "Sound", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Erik Brandsma", LineType::Default, titelSpacing ) );

	lines->push_back( createLine( renderTarget, "Git Master", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Edwin Hattink", LineType::Default, titelSpacing ) );

	lines->push_back( createLine( renderTarget, "Test Manager", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Ivan Horn", LineType::Default, titelSpacing ) );

	lines->push_back( createLine( renderTarget, "Scrum master", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Erik Brandsma", LineType::Default, titelSpacing ) );

	lines->push_back( createLine( renderTarget, "Product owner", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Edwin Hattink", LineType::Default, titelSpacing ) );

	lines->push_back( createLine( renderTarget, "Boss", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Bob van der Putten", LineType::Default, titelSpacing ) );

	lines->push_back( createLine( renderTarget, "Customer", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Bob van der putten", LineType::Default, titelSpacing ) );

	lines->push_back( createLine( renderTarget, "Special thanks", LineType::Titel, largerMargin ) );
	lines->push_back( createLine( renderTarget, "Wokmeneer", LineType::Default, titelSpacing ) );
	lines->push_back( createLine( renderTarget, "Die ene dönerzaak", LineType::Default, titelSpacing ) );
	lines->push_back( createLine( renderTarget, "OB205", LineType::Default, titelSpacing ) );
	lines->push_back( createLine( renderTarget, "Google", LineType::Default, titelSpacing ) );
	lines->push_back( createLine( renderTarget, "Stackoverflow", LineType::Default, titelSpacing ) );
	lines->push_back( createLine( renderTarget, "iForce2d tutorials", LineType::Default, titelSpacing ) );
	lines->push_back( createLine( renderTarget, "CodingMadeEasy tutorials", LineType::Default, titelSpacing ) );
	lines->push_back( createLine( renderTarget, "Thecplusplusguy tutorials", LineType::Default, titelSpacing ) );

	lines->push_back( createLine( renderTarget, "Thanks for playing!", LineType::MainTitel, cameraRect->h / 2 ) );
}

CreditsMenu::~CreditsMenu()
{
	for( size_t c = 0; c < lines->size(); c++ )
	{
		delete lines->at( c )->first;		lines->at( c )->first = nullptr;
		delete lines->at( c );				lines->at( c ) = nullptr;
	}
	delete lines;

	for( size_t x = 0; x < menuItems->size(); x++ )
	{
		delete menuItems->at( x );			menuItems->at( x ) = nullptr;
	}
	delete menuItems;						menuItems = nullptr;

	TTF_CloseFont( creditsDefaultFont );	creditsDefaultFont = nullptr;
	TTF_CloseFont( creditsMainTitelFont );	creditsMainTitelFont = nullptr;
	TTF_CloseFont( creditsTitelFont );		creditsTitelFont = nullptr;
}

std::pair<MenuItem*, int>* CreditsMenu::createLine( SDL_Renderer* renderTarget, char * line, LineType lineType, int margin )
{
	TTF_Font* fontToUse;
	Color colorToUse;

	switch( lineType )
	{
		case(LineType::Titel) :
			fontToUse = creditsTitelFont;
			colorToUse = Color::Red;
			break;
		case(LineType::Default) :
			fontToUse = creditsDefaultFont;
			colorToUse = Color::White;
			break;
		case(LineType::MainTitel) :
			fontToUse = creditsMainTitelFont;
			colorToUse = Color::White;
	}

	MenuItem* menuItem = new MenuItem( renderTarget, fontToUse, line );
	menuItem->setColor( renderTarget, colorToUse );
	return new std::pair<MenuItem*, int>( menuItem, margin );
}

int CreditsMenu::showMenu( SDL_Renderer* renderTarget )
{
	previousTime = SDL_GetTicks();;
	currentTime = SDL_GetTicks();;
	deltaTime = 0.0f;
	pastTime = 0.0f;
	positionAllLines();

	sound->stopSound( Sound_MainMenu_Theme );
	sound->playSound( Sound_Credits_Theme );

	int choice = createMenu( renderTarget );
	switch( choice )
	{
		case(Choices::Back) :
			sound->fadeOut();
			sound->stopSound( Sound_Credits_Theme );
			sound->playSoundLooping( Sound_MainMenu_Theme, 0.5f );
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

int CreditsMenu::createMenu( SDL_Renderer* renderTarget )
{
	SDL_Event event;
	bool needsToFadeIn = true;
	while( 1 )
	{
		if( sound->getVolume() != 1.00f && needsToFadeIn )
			sound->fadeInTick();
		else
			needsToFadeIn = false;

		previousTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - previousTime) / 1000.0f;
		while( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
				case SDL_QUIT:
					return Choices::Exit;
					break;
				case SDL_MOUSEMOTION:
					mouseX = event.motion.x;
					mouseY = event.motion.y;
					for( size_t i = 0; i < menuItems->size(); i++ )
						menuItems->at( i )->checkHover( mouseX, mouseY );
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouseX = event.motion.x;
					mouseY = event.motion.y;
					for( size_t index = 0; index < menuItems->size(); index++ )
						if( mouseX >= menuItems->at( index )->getXPosition() && mouseX <= menuItems->at( index )->getXPosition() + menuItems->at( index )->getWidth() &&
							mouseY >= menuItems->at( index )->getYPosition() && mouseY <= menuItems->at( index )->getYPosition() + menuItems->at( index )->getHeight() )
						{
							sound->playSound( Sound_MainMenu_Click );
							return index;
						}
					break;
			}
		}
		if( isDone() )
			return Choices::Back;

		SDL_RenderClear( renderTarget );
		update( deltaTime );
		draw( renderTarget );
		SDL_RenderPresent( renderTarget );
		SDL_Delay( 1000 / 60 );
	}
}

void CreditsMenu::update( float deltaTime )
{
	if( shouldMove( deltaTime ) )
	{
		float fps = (1 / deltaTime);
		int pixels = int( round( speed / fps ) );
		for( size_t c = 0; c < lines->size(); c++ )
			lines->at( c )->first->setYPosition( lines->at( c )->first->getYPosition() - pixels );
	}
}

bool CreditsMenu::shouldMove( float deltaTime )
{

	if( pastTime > 2.5f )
		return true;
	else
		pastTime += deltaTime;
	return false;
}

bool CreditsMenu::isDone()
{
	if( lines->at( lines->size() - 1 )->first->getYPosition() < -100 )
	{
		if( sound->getVolume() != 0.00f )
		{
			sound->fadeOutTick();
		}
		else
			return true;
	}
	return false;

}

void CreditsMenu::draw( SDL_Renderer* renderTarget )
{
	for( size_t c = 0; c < lines->size(); c++ )
		lines->at( c )->first->draw( renderTarget );
	for( size_t x = 0; x < menuItems->size(); x++ )
		menuItems->at( x )->draw( renderTarget );
}

void CreditsMenu::positionAllLines()
{
	for( size_t c = 0; c < lines->size(); c++ )
	{
		MenuItem* item = lines->at( c )->first;
		int previousDistance = 0;
		for( size_t x = 0; x <= c; x++ )
			previousDistance += (lines->at( x )->first->getHeight() + lines->at( x )->second);

		if( c == 0 )
			previousDistance = 0;

		item->setYPosition( cameraRect->h / 2 - item->getHeight() / 2 + previousDistance );
		item->setXPosition( cameraRect->w / 2 - item->getWidth() / 2 );
	}
}

int CreditsMenu::getBackCode()
{
	return Choices::Back;
}

int CreditsMenu::getExitCode()
{
	return Choices::Exit;
}