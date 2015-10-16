#ifndef MENUITEM_H
#define MENUITEM_H
#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>

class MenuItem
{
private:
	SDL_Rect position;
	char* content;
	SDL_Texture* currentTexture;
	SDL_Texture* normalTexture;
	SDL_Texture* highlightedTexture;
	bool selected;
	SDL_Color normalColor;
	SDL_Color highlightedColor;
	TTF_Font* myFont;

	SDL_Texture* createTextTexture(SDL_Renderer* renderTarget, TTF_Font* font, const char* text, SDL_Color color);
	void toggleSelected();

public:
	MenuItem(SDL_Renderer* renderTarget, TTF_Font* font, char* content);
	~MenuItem();

	void setPosition(SDL_Rect position);
	bool checkHover(int x, int y);

	int getHeight();
	int getWidth();
	int getXPosition();
	int getYPosition();
	void setXPositon(int xPosition);
	void setYPosition(int yPosition);
	void setText(SDL_Renderer* renderTarget, char* text);
	void draw(SDL_Renderer* renderTarget);
};

#endif

