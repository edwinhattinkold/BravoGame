#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H
#include "SDL.h"
#include "Sound.h"
#include <vector>
#include "MenuItem.h"
#include "Settings.h"
#include "wtypes.h"
#include "Camera.h"

class OptionsMenu
{
private:
	SDL_Window* window;
	SDL_Renderer* renderTarget;
	SDL_Rect backgroundImageRect;
	Camera* camera;
	SDL_Texture* backgroundImage;
	SDL_Event ev;
	std::vector<MenuItem*>* menuItems;
	Sound* sound;
	Uint32 time;
	int mouseX, mouseY, margin, combinedHeight;
	bool soundOn;
	bool fullscreen;
	static enum Choices { FullScreen_On_Off, Sound_On_Off, Back, Exit, Size };
	void center();
	Settings* settings;
	void updateSound( SDL_Renderer* renderTarget );
	void toggleSound( SDL_Renderer* renderTarget );

	void updateFullscreen( SDL_Renderer* renderTarget );
	void toggleFullscreen( SDL_Renderer* renderTarget );

	int selected;

public:
	OptionsMenu( SDL_Renderer* renderTarget, SDL_Window* window, SDL_Texture* backgroundImage, Camera* camera, TTF_Font* font );
	~OptionsMenu();

	int getBackCode();
	int getExitCode();
	void draw(SDL_Renderer* renderTarget);
	int showMenu(SDL_Renderer* renderTarget);
	int createMenu(SDL_Renderer* renderTarget);
	void getDesktopResolution( int& horizontal, int& vertical );
	void handleKeyboardInput( SDL_Keycode keyPressed );
	void updateSelected();
	void handleSelection( int index );
};

#endif


