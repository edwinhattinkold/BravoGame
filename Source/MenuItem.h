#ifndef MENUITEM_H
#define MENUITEM_H
#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>

static enum Color { Red, White, SelectedRed };

using namespace std;
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
	void setContent(SDL_Renderer* renderTarget, char* text);

public:
	MenuItem(SDL_Renderer* renderTarget, TTF_Font* font, char* content);
	~MenuItem();

	void setPosition(SDL_Rect position);
	bool checkHover(int x, int y);

	int getHeight();
	int getWidth();
	int getXPosition();
	int getYPosition();
	void setColor(SDL_Renderer* renderTarget, Color color);
	void setHighlighted();
	void setXPosition(int xPosition);
	void setYPosition(int yPosition);

	void setText( SDL_Renderer* renderTarget, char* text );
	void setText( SDL_Renderer* renderTarget, string text );

	void draw(SDL_Renderer* renderTarget);
};

#endif

